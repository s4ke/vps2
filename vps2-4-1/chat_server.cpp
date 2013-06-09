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
map<string, vector<client_info_t> > clients; 
map<string, vector<string> > to_send;

int main(int argc, char** argv) {
	struct sockaddr_in serv_addr;
    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    	bzero(&serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	serv_addr.sin_port = htons(9877);
	bind(sockfd, (struct sockaddr *) &serv_addr, MESSAGE_LENGTH);

	pthread_t rec;
	pthread_t snd;
	pthread_create(&rec, NULL, receiver, NULL);
	pthread_create(&snd, NULL, sender, NULL); 

	pthread_join(rec, NULL);
	pthread_join(snd, NULL);
}

void* receiver(void *args) {
	while(1) {
		
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
		}	
	}

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
