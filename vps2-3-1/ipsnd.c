#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char** argv)
{
	const int MAGIC_REQUIRED_BYTES = 12;
	int port = 60000;
	int magic_numbers[3];
	int snd_sock = 0;
	int stream_sock = 0;
	struct sockaddr_in address;
	unsigned int srv_address_len;
	struct sockaddr_in srv_address;
	char buffer[256];
	int recv_len, magic_len;
	int quit = 0;
	char* input_line = NULL;
	struct hostent *server;

	if(argc < 3)  {
	   fprintf(stderr, "Too few arguments.\n");
	}



	port = atoi(argv[2]);
	server = gethostbyname(argv[1]);
	if(server == NULL) {
	   fprintf(stderr, "Invalid Server.\n");
	   return -1;
	}


	snd_sock = socket(AF_INET, SOCK_STREAM, 0);

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

	if(connect(snd_sock, (struct sockaddr *) &srv_address, sizeof(srv_address)) < 0) {
		fprintf(stderr, "Connection failed.\n");
		exit(-1);
	}

	magic_numbers[0] = 21;
	magic_numbers[1] = 42;
	magic_numbers[2] = 63;

	write(snd_sock, magic_numbers, MAGIC_REQUIRED_BYTES);


	fprintf(stderr, "Start Typing!\n");


	do {
		bzero(buffer,256);
		input_line = fgets(buffer, 255, stdin);
		if(input_line != NULL) {
			write(snd_sock, buffer, strlen(buffer));
		}
	
	} while (input_line != NULL);
	close(snd_sock);


	return 0;
}
