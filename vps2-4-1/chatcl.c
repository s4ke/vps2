#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

int quit = 0;

void* output_thread(void* socket)
{
char buffer[4097];
int rcv_sock = *((int*)socket);
int recv_len = 0;

do {
	bzero(buffer,4097);
	recv_len = recvfrom(rcv_sock, buffer, 4096, 0, NULL, NULL);
	if(recv_len < 0 && !quit) {
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
char buffer[256];
int recv_len;

char* input_line = NULL;
struct hostent *server;

if(argc < 4)  {
   fprintf(stderr, "Too few arguments.\n usage: chatcl <server> <port> <chatroom>");
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

fprintf(stderr, "Joined Room %s!\n", argv[3]);
fprintf(stderr, "Start Typing!\n");


do {
	bzero(buffer,256);
	input_line = fgets(buffer, 255, stdin);
	if(input_line != NULL) {
		write(snd_sock, buffer, strlen(buffer));
	}
	
} while (input_line != NULL && strlen(input_line) > 1);

fprintf(stderr, "Closing connection!\n");
close(snd_sock);
quit = 1;

pthread_join(output, NULL);

return 0;
}
