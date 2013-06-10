/**
 * File: chat_server.cpp
 * Authors: Martin Braun, Georg Rollinger, Robert Günther
 * This server allows you to communicate with the a chat client like
 * the one in this repository in the chatcl.cpp file.
 * 
 * You can specify the port the server is listening on
 * via a command line parameter.
 * 
 * Furthermore this server doesn't use multicast
 * because of the way the threads are realized.
 * If we changed the way that is done to always
 * sending all the messages to everyone and
 * then letting the client decide we could achieve
 * the same behaviour like now but with multicast.
 * However the current design was easier to implement.
 * 
 * We are using pthreads for the multithreading
 * and the synchronization of the program.
 * So please compile this .cpp file
 * with something like:
 * 
 * 	g++ chat_server.cpp -lpthread -o chatserver
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string>
#include <map>
#include <vector>
#include <pthread.h>
#include <algorithm>
#include <arpa/inet.h>
#include <sstream>

const int MESSAGE_LENGTH = 4096;

using namespace std;

void* receiver(void* args);
void* sender(void* args);

typedef struct _client_info_t {
   struct sockaddr_in address;
   socklen_t addrlen; 
} client_info_t;

int sockfd;
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t send_buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
//mapping: room -> client
map<string, vector<client_info_t> > clients; 
//mapping: room -> list of messages
map<string, vector<string> > to_send;
//mapping: ip -> room
map<string, string> connected_ips;

int main(int argc, char** argv) {	
	if(argc != 2) {
		printf("usage: %s <port>\n", argv[0]);
		return -1;	
	}
	struct sockaddr_in serv_addr;
	printf("opening socket...\n");
    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    	bzero(&serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	serv_addr.sin_port = htons(atoi(argv[1]));
	printf("binding...\n");
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	printf("creating threads...\n");
	pthread_t rec;
	pthread_t snd;
	pthread_create(&rec, NULL, receiver, NULL);
	pthread_create(&snd, NULL, sender, NULL); 

	pthread_join(rec, NULL);
	pthread_join(snd, NULL);
}

void* receiver(void *args) {
	while(1) {
		char buf[MESSAGE_LENGTH];
		bzero(buf, sizeof(buf));
		client_info_t client_info;
		client_info.addrlen = sizeof(client_info.address);
		//for SOCK_DGRAM we only have
		//to call the recvfrom(...) methode once
		ssize_t rec = recvfrom(sockfd,
			buf, sizeof(buf),
			0, (struct sockaddr*) &client_info.address,
			&client_info.addrlen);	
		
		char ip[100];	
		if(inet_ntop(AF_INET, &client_info.address.sin_addr,
			ip, client_info.addrlen) == NULL) {
			printf("couldn't convert ip to string");
			continue;
		}

	 	stringstream builder;
		builder << ip << ":" << client_info.address.sin_port;
		string ipString = builder.str();

		printf("ip: %s\n", ipString.c_str());
		if(connected_ips.find(ipString) == connected_ips.end()) {
			pthread_mutex_lock(&client_mutex);
			
			string room = buf;
			connected_ips[ipString] = room;	
			clients[room].push_back(client_info);	
			printf("someone joined %s.\n", room.c_str());
	
			pthread_mutex_unlock(&client_mutex);		
		} else {
			pthread_mutex_lock(&send_buffer_mutex);

			//get the room of the ip
			string room = connected_ips[ipString];
			string message = buf;
			to_send[room].push_back(message);
			printf("message received: %s\n", message.c_str());

			pthread_mutex_unlock(&send_buffer_mutex);	
		}		
	}	
}



void send_to_all_clients(pair<const string, vector<string> >& pair) {
	pthread_mutex_lock(&client_mutex);

	//pair.first holds the thread name
	vector<client_info_t> recipients = clients[pair.first];
	for(vector<client_info_t>::size_type i = 0; i != recipients.size(); ++i) {
		//pair.second is the list of messages to send
		for(vector<string>::size_type j = 0; j != pair.second.size(); ++j) {
			sendto(sockfd, pair.second[j].c_str(),
				pair.second[j].length(),
				0, (struct sockaddr *) &recipients[i].address,
				recipients[i].addrlen);				
			char ip[100];	
			if(inet_ntop(AF_INET, &recipients[i].address.sin_addr,
				ip, recipients[i].addrlen) == NULL) {
				printf("couldn't convert ip to string");
				continue;
			}
			stringstream builder;
			builder << ip << ":" << recipients[i].address.sin_port;
			string ipString = builder.str();
			
			printf("sending to %s\n: %s\n", ipString.c_str(), pair.second[j].c_str());
		}	
	}
	pair.second.clear();

	pthread_mutex_unlock(&client_mutex);
}


void* sender(void *args) {
	while(1) {
		pthread_mutex_lock(&send_buffer_mutex);
		for_each(to_send.begin(), to_send.end(), send_to_all_clients);
		to_send.clear();
		pthread_mutex_unlock(&send_buffer_mutex);
		sleep(1);
	}
}
