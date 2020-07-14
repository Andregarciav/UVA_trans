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
    struct sockaddr_in6;

    int tam_pkt = 0; //sempre que possivel inicialize variável com algum valor, só não set em caso de competição como URIjudge
    int num_pkt = 0;
    char *ip_server;
    char *porta_server;



    fd_set fds;
    clock_t inicio, final , startTime , endTime;

    struct timeval tv;
    


    struct addrinfo hints, *list, *item;
    /* Checking the arguments */
    if(argc != 5) {
        printf("\n[CLIENT] Error Args.\n\n");
        printf("./cliente [IP servidor] [Porta servidor] [tamanho do pacote] [numero de pacotes]\n");
        exit(EXIT_FAILURE);
    }
    
    /* Após a verificação vamos salvar os argumentos já como variáveis, fica melhor*/
    ip_server       = argv[1];
    porta_server    = argv[2];
    tam_pkt         = atoi(argv[3]); //não faça cast de char para int ele vai usar tabela ascii
    num_pkt         = atoi(argv[4]);


    memset(&hints, 0, sizeof hints);    // Fills the struct with zeros
    hints.ai_family = AF_UNSPEC;        // Allows IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;     // Only UDP

    if((rv = getaddrinfo(ip_server, porta_server, &hints, &list)) != 0) { // argv[1] address argv[2] port
        printf("[CLIENT] Error bad getaddrinfo: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
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
    int tam_payload = tam_pkt - 6 - 13;// 6 do tamanho do header udp (8 - 2 da checksum) e 13 do pacote do openvlc
    int tam_dados = tam_payload-2-2;
    //tem -2-2 representando a checksum e o identificador
    //convertendo de int pra char
    char msg[tam_payload];//msg  = identificador + dados + checksum
    uint16_t checksum = 0;
    uint16_t id = 0;
    FD_ZERO(&fds);//Reseta todos os bits
    FD_SET (client_socket, &fds);
    FILE *fp;
    fp = fopen("/home/gabriel/Desktop/teste1.txt", "w");
    for(int i =0; i<(int)num_pkt; i++) {
            // memset(&buffer, 0, sizeof(buffer));//Zera Memoria da variável
            FD_ZERO(&fds);//Reseta todos os bits
            FD_SET (client_socket, &fds); //Estabelece o bit que corresponde ao socket clientSocket
            tv.tv_sec = 2; //Estabelece o valor de time out de 7 segundos
            tv.tv_usec = 0; //Estabeele o valor de time de 0 milissegundos
            int n = select(client_socket, &fds, NULL, NULL, &tv);
            // if(n <= 0)
            // {
            //     perror("ERROR Server : select()\n");
            //     close(client_socket);
            //     exit(1);
            // }
            // else {
            while (n != 0);    
                if (i == num_pkt - 1) {
                    // *msg = 's';
                    // melhor fazer assim
                    msg[0] = 's';
                    msg[1] = '\0';
                } else {
                    id = id +1;
                    msg[0] = (uint8_t)((id >> 8) & 0xff);
        	    msg[1] = (uint8_t)(id & 0xff);
                    geraPayload(tam_dados, msg);
                    checksum = calculaChecksum(msg, tam_payload);
                    msg[tam_payload-2] = (uint8_t)((checksum >> 8) & 0xff);
        	    msg[tam_payload-1] = (uint8_t)(checksum & 0xff);
                }
		int j=0;
while(j<tam_payload){
fprintf(fp,"%c", msg[j]);
j++;
}
fprintf(fp, "\n");
                bytes = strlen(msg);
                write(client_socket, msg, bytes);
                memset(&msg, 0, sizeof(msg)); //Zera Memoria da variável
            // }

    }
    
    close(client_socket); // Releasing the socket.
    freeaddrinfo(list); // Releasing the memory!!
    return 0;
}
