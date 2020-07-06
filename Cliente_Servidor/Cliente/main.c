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
#include <sys/select.h>
#include "Funcoes.h"

//arg[3] = tam_pacote, arg[4] = num_pacotes
int main(int argc, char** argv) {

    int client_socket, bytes, rv;
    char* ip_src, *ip_dest = argv[1];
    ip_src = "127.0.0.1";
    struct sockaddr_in6;

    fd_set fds;
    clock_t inicio, final , startTime , endTime;


    struct addrinfo hints, *list, *item;
    /* Checking the arguments */
    if(argc != 5) {
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
    printf("[CLIENT] Connected!\n");
    int tam_payload = (int)argv[3] - 6 - 13 - sizeof(ip_src)- sizeof(ip_dest)- htons(IPPROTO_UDP);;
    int tam_dados = tam_payload-5-5;
    //tem -5-5 representando a checksum e o identificador
    //16 bits representam até 65000, mas não consegui fazer 16 bits serem 2 bytes então coloquei como 5 bytes
    //convertendo de int pra char
    char *msg = NULL;//msg  = identificador + dados + checksum
    char *dados = NULL;
    uint16_t checksum = 0;
    uint16_t id = 0;
    char check_string[5];
    char id_string[5];
    FD_ZERO(&fds);//Reseta todos os bits
    FD_SET (client_socket, &fds);
    for(int i =0; i<(int)(argv[4]); i++) {
            msg = malloc(tam_payload * sizeof(char));
            memset(&buffer, 0, sizeof(buffer));//Zera Memoria da variável
            FD_ZERO(&fds);//Reseta todos os bits
            FD_SET (client_socket, &fds);
            int n = select(client_socket+1, NULL, &fds, NULL, NULL);
            if(n <= 0)
            {
                perror("ERROR Server : select()\n");
                close(client_socket);
                exit(1);
            }
            else {
                if (i == (int) (argv[4]) - 1) {
                    *msg = 's';
                } else {
                    id++;
                    sprintf(id_string, "%u", id);
                    strcat(msg, id_string);
                    strcat(msg, dados = geraPayload(tam_dados));
                    checksum = calculaChecksum(msg, tam_payload + 1, ip_src, ip_dest);
                    sprintf(check_string, "%u", checksum);
                    strcat(msg, check_string);
                }
                bytes = strlen(msg);
                write(client_socket, msg, bytes);
                memset(&msg, 0, sizeof(msg)); //Zera Memoria da variável
                free(msg);
            }

    }

    close(client_socket); // Releasing the socket.
    freeaddrinfo(list); // Releasing the memory!!
    return 0;
}