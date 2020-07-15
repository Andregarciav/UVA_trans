#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "Funcoes.h"

int main(int argc, char** argv) {
  int i, udpSocket, nBytes;
  socklen_t size;
  struct sockaddr_in serverAddr, clientAddr;

  /* Checking the arguments */
  if(argc != 4) {
    printf("\n[SERVIDOR] Argument error.\n\n");
    printf("./servidor [numero da porta] [arquivo de destino] [tam do pacote]\n");
    exit(1);
  }

  /* Creating UDP socket */
  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);  // AF_INET--> IPv4, SOCK_DGRAM --> UDP

  if (udpSocket == -1) {
      printf("\n[SERVIDOR] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;            // IPv4
  serverAddr.sin_addr.s_addr = INADDR_ANY;    // Any IP address for the server
  serverAddr.sin_port = htons(atoi(argv[1])); // Gets the port number by the first argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // For compatibility

  /* Bind socket with address struct */
  if( bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    printf("\n[SERVIDOR] Bind Error\n\n");
    exit(1);
  }

  size = sizeof(struct sockaddr_in);
  int tam_pkt = 0;
  tam_pkt = atoi(argv[3]);
  int tam_payload = tam_pkt - 6 - 13 -20;
  char buffer[tam_payload];
  FILE *fp;
  char *arquivo;
  arquivo = argv[2];
  fp = fopen(arquivo, "w");
  if(fp==NULL) {
      printf("Arquivo inválido!");
      exit(1);
  }
  int id, contador = 0;
  uint8_t aux1, aux2;
  printf("[SERVIDOR] Waiting for messages...\n\n");
  int j =0;
  while(1) {
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on clientAddr variable */
      j=0;
      memset(&buffer, 0, sizeof(buffer));
      recvfrom(udpSocket, buffer, 2000, 0, (struct sockaddr *) &clientAddr, &size);
      if (buffer[0] == 's' && buffer[1] == '\0') {
                printf("\nFINAL DA TRANSMISSAO \n");
                printf("Contador: %d\n", contador);
                fclose(fp);
                break;
            }
     else if(avaliador(buffer, tam_payload) == 1) {
         contador ++;
           }
     aux1 = buffer[0];
     aux2 = buffer[1];
     id = (aux1 << 8) | aux2;
     fprintf(fp,"ID %d\n", id);


    /* Convert message received to uppercase */
    //for(i=0; i < nBytes-1; i++) buffer[i] = toupper(buffer[i]);

    /* Send uppercase message back to client, using serverStorage as the address */
    //sendto(udpSocket, buffer, nBytes, 0, (struct sockaddr *) &clientAddr, size);
  }

  return 0;
}