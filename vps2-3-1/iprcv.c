#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	const int MAGIC_REQUIRED_BYTES = 12;
	int port = 60000;
	int magic_numbers[3];
	int rcv_sock = 0;
	int stream_sock = 0;
	struct sockaddr_in address;
	unsigned int cli_address_len;
	struct sockaddr_in cli_address;
	char buffer[1024];
	int recv_len, magic_len;
	int quit = 0;
    int bytes_rec = 0;
    double elapsed = 0.0;
    struct timeval tv;
    struct timeval start_tv;

	if(argc > 1) {
	   port = atoi(argv[1]);
	}


	rcv_sock = socket(AF_INET, SOCK_STREAM, 0);

	if(rcv_sock < 0) {
	   fprintf(stderr, "Socket creation failed.\n");
	   return -1;
	}
	bzero((char*) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	if(bind(rcv_sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
	   fprintf(stderr, "Binding failed.");
	}

	listen(rcv_sock, 5);
	fprintf(stderr, "Listening on %i\n", port);


	while(!quit) {
		cli_address_len = sizeof(cli_address);
		stream_sock = accept(rcv_sock, (struct sockaddr *) &cli_address, &cli_address_len);
		if(stream_sock < 0) {
		   fprintf(stderr, "Accept failed.\n");
		} else {
			fprintf(stderr, "Accepted.\n");
		}
	

		bzero((char*)magic_numbers, MAGIC_REQUIRED_BYTES);
		magic_len = 0;
		while(magic_len < MAGIC_REQUIRED_BYTES) {
		   recv_len = read(stream_sock, (char*)(&magic_numbers[0])+magic_len, MAGIC_REQUIRED_BYTES - magic_len);
		   if(recv_len < 0) {
			  fprintf(stderr, "Receiving magic failed.\n");
		   } else {
			  magic_len += recv_len;	   
		   }
		}

		if(magic_numbers[0] == 21 && magic_numbers[1] == 42 && magic_numbers[2] == 63) {
           do { 
                bzero(buffer, sizeof(buffer));
                gettimeofday(&start_tv, NULL);
				recv_len = read(stream_sock, buffer, sizeof(buffer) - 1);
				gettimeofday(&tv, NULL);
                if(recv_len < 0) {
					fprintf(stderr, "Read failed.\n");
				} else {
					fprintf(stdout, "%s", buffer);
				}
                if(recv_len > 0) {
                    elapsed += (tv.tv_sec - start_tv.tv_sec) +
                      (tv.tv_usec - start_tv.tv_usec) / 1000000.0;
                    bytes_rec += recv_len;
                }
			} while (recv_len > 0);
            quit = 1;
            fprintf(stderr, "took %f seconds to receive %d bytes\n", elapsed, bytes_rec);
		} else {
			fprintf(stderr, "Wrong magic.\n");
		}
		close(stream_sock);
	}
	close(rcv_sock);

	return 0;
}
