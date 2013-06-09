#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>

int quit = 0;

void* output_thread(void* socket)
{
char buffer[4097];
int rcv_sock = *((int*)socket);
int recv_len = 0;

fprintf(stderr, "Receiving.\n");
do {
	bzero(buffer,4097);
	recv_len = recvfrom(rcv_sock, buffer, 4096, 0, NULL, NULL);
	if(recv_len < 0) {
		fprintf(stderr, "Rcv failed.\n");
	} else {
		fprintf(stdout, "%s", buffer);
	}
} while (!quit);

return NULL;
}

int main(int argc, char** argv)
{
pthread_attr_t thread_attr;
pthread_t output;
int port = 60000;
int snd_sock = 0;
struct sockaddr_in address;
unsigned int srv_address_len;
struct sockaddr_in srv_address;
char buffer[4096];
char* msgbuffer;
int recv_len;
int nick_len;

char* input_line = NULL;
struct hostent *server;

if(argc < 5)  {
   fprintf(stderr, "Too few arguments. usage: chatcl <server> <port> <chatroom> <nick>");
   return -1;
}



port = atoi(argv[2]);
server = gethostbyname(argv[1]);
if(server == NULL) {
   fprintf(stderr, "Invalid Server.\n");
   return -1;
}


snd_sock = socket(AF_INET, SOCK_DGRAM, 0);

if(snd_sock < 0) {
   fprintf(stderr, "Socket creation failed.\n");
   return -1;
}

bzero((char*) &srv_address, sizeof(srv_address));
srv_address.sin_family = AF_INET;
bcopy((char*)server->h_addr,
	(char*)&srv_address.sin_addr.s_addr,
	server->h_length);
srv_address.sin_port = htons(port);

pthread_attr_init(&thread_attr);

pthread_create(&output, 
        &thread_attr,
        &output_thread,
        &snd_sock);
        

sendto(snd_sock, argv[3], strlen(argv[3]), 0,(struct sockaddr*) &srv_address, sizeof(srv_address));

nick_len = strlen(argv[4]);
strcpy(buffer, argv[4]);
buffer[nick_len++] = ':';
buffer[nick_len++] = ' ';
msgbuffer = buffer + nick_len;


fprintf(stderr, "Joined Room %s!\n", argv[3]);
fprintf(stderr, "As %s!\n", argv[4]);
fprintf(stderr, "Start Typing!\n");



do {
	bzero(msgbuffer,4096 - nick_len);
	input_line = fgets(msgbuffer, 4095 - nick_len, stdin);
	if(input_line != NULL) {
		sendto(snd_sock, buffer, strlen(buffer), 0,(struct sockaddr*) &srv_address, sizeof(srv_address));	
	}
	
} while (input_line != NULL && strlen(input_line) > 1);

fprintf(stderr, "Closing connection!\n");
close(snd_sock);
quit = 1;

pthread_join(output, NULL);

return 0;
}
