#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


int main(int argc, char** argv) {

	int client_socket, bytes, rv;
    struct sockaddr_in6;
  
	fd_set fds;
	clock_t inicio, final , startTime , endTime;


	struct addrinfo hints, *list, *item;
	/* Checking the arguments */
  	if(argc != 3) {
    	printf("\n[CLIENT] Error Args.\n\n");
    	exit(1);
  	}

  	memset(&hints, 0, sizeof hints);    // Fills the struct with zeros
  	hints.ai_family = AF_UNSPEC;        // Allows IPv4 or IPv6
  	hints.ai_socktype = SOCK_DGRAM;     // Only UDP

  	if((rv = getaddrinfo(argv[1], argv[2], &hints, &list)) != 0) { // argv[1] address argv[2] port
    	printf("[CLIENT] Error bad getaddrinfo: %s\n", gai_strerror(rv));
    	exit(1);
  	}


    // ------------------------------------------------------------
    // For each item in the function...
 	for(item = list; item != NULL; item = item->ai_next) {
    // Try to create the socket
    	if((client_socket = socket(item->ai_family, item->ai_socktype, item->ai_protocol)) == -1) {
      		continue;
    	}
		// If creates the socket, try to connect:
    	if(connect(client_socket, item->ai_addr, item->ai_addrlen) == -1) {
      		close(client_socket); // Did not work! Close the socket and try again.
      		printf("[CLIENT]: Error connection\n");
      		continue;
    	}
    	break;
    }

    if(item == NULL) exit(1); // Caso todos os itens falhem, será o fim da lista.
 // ------------------------------------------------------------
 // A partir deste ponto, estamos conectados!
 // ------------------------------------------------------------


 	char msg[20];
  	printf("[CLIENT] Connected!\n");

	FD_ZERO(&fds);//Reseta todos os bits
	FD_SET (client_socket, &fds);

	memset(&msg, 0, sizeof(msg)); //Zera Memoria da variável
	memset(&buffer, 0, sizeof(buffer));
			
	bytes = strlen(msg);
	write(client_socket, msg , bytes);
			
  	close(client_socket); // Releasing the socket.
  	freeaddrinfo(list); // Releasing the memory!!
	return 0;
}
