/* SERVIDOR UDP PARA ANALISE DE TRÁFIGO DE DADOS
 * O SERVIDOR TEM COMO BASE RECEBER UMA MENSAGEM UDP
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Funcoes.h"
//biblioteca de definoções para contar o numero de mensagens recebidas



int main(int argc, char** argv)
{
    int server_socket, v6only;
    int tam_pkt = 0;
    tam_pkt = atoi(argv[3]);
    int tam_payload = tam_pkt - 6 - 13;
    char buffer[tam_payload];
    unsigned int size;

    struct sockaddr_in6 server_addr, client_addr;

    if(argc != 4) {
        printf("\n[SERVIDOR] Erro nos argumentos.\n\n");
        printf("./servidor [numero da porta] [arquivo de destino] [tam do pacote]\n");
        exit(1);
    }
    server_socket = socket( AF_INET6, SOCK_DGRAM , 0 );
    //AF_INET6 é IPv6 e SOCK_DGRAM cria socket UDP
    if (server_socket == -1)
    {
        printf("[SERVIDOR] Erro ao criar socket");
        exit(1);
    }
    // Socket funcionando IPv(4)6
    v6only = 0;
    if (setsockopt(server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0)
    {
        printf("\n[SERVIDOR] Erron no Socket IPv6/IPv4.\n\n");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));   // Cleaning the entire struct

    server_addr.sin6_family = AF_INET6;           // IPv6
    server_addr.sin6_addr = in6addr_any;          // Any IP address for the server
    server_addr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument

    /* Bind socket with address struct */
    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        printf("\n[SERVIDOR] Erro de Bind\n\n");
        exit(1);
    }

    size = sizeof(struct sockaddr_in6);
    printf("[SERVIDOR] Esperando cliente\n");
    fd_set read_fds;

    FILE *fp;
    char *arquivo;
    arquivo = argv[2];
    fp = fopen(arquivo, "w");
    if(fp==NULL){
        printf("Arquivo inválido!");
        exit(1);
    }
    int id, contador = 0;
    uint8_t aux1, aux2;
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        //O que ta comentando aqui é a parte de delay
        //FD_ZERO(&read_fds);
        //FD_SET(server_socket, &read_fds);
        //int n = select(server_socket+1, &read_fds, NULL, NULL, NULL);
        //if(n <= 0)
       // {
            //perror("ERROR Server : select()\n");
           // close(server_socket);
           // exit(1);
       // }
       // else {
            recvfrom(server_socket, buffer, 2000, 0, (struct sockaddr *) &client_addr, &size); //Recebe a mensagem do cliente
	    		int j=0;
while(j<tam_payload){
fprintf(fp,"%c", buffer[j]);
j++;
}
fprintf(fp, "\n");
            if (*buffer == 's') {
                printf("\nFINAL DA TRANSMISSAO \n");
                printf("Contado: %d\n", contador);
                fclose(fp);
                break;
            }
            else if(avaliador(buffer, tam_payload) == 1) {
                contador ++;
           }
	   aux1 = buffer[0];
           aux2 = buffer[1];
           id = (aux1 << 8) | aux2;
        //}
    }


    return 0;
}
