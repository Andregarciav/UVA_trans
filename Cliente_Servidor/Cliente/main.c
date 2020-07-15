#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "Funcoes.h"

int main(int argc, char** argv) {
  int clientSocket, nBytes;
  socklen_t size;
  struct sockaddr_in serverAddr;
  int tam_pkt = 0;
  int num_pkt =0;


  /* Checking the Arguments */
  if(argc != 5) {
    printf("\n[CLIENT] Argument error.\n\n");
    printf("./cliente [IP servidor] [Porta servidor] [tamanho do pacote] [numero de pacotes]\n");
    exit(1);
  }

  /* Create UDP socket */
  clientSocket = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET --> IPv4, SOCK_DGRAM --> UDP

  if (clientSocket == -1) {
      printf("\n[CLIENT] Socket error.\n\n");
      exit(1);
  }

  /* Configure settings in address struct */
  serverAddr.sin_family = AF_INET;                 // IPv4
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]); // Get the IP address by the argument
  serverAddr.sin_port = htons(atoi(argv[2]));      // Get the port by the argument

  memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero); // for compatibility

  size = sizeof(struct sockaddr_in);

  tam_pkt = atoi(argv[3]);
  num_pkt = atoi(argv[4]);
  int tam_payload = tam_pkt - 6 - 13 - 20;
  int tam_dados = tam_payload -2-2;
  char buffer[tam_payload];
  uint16_t checksum = 0;
  uint16_t id = 16384;
  fd_set fds;
  FD_ZERO(&fds);//Reseta todos os bits
  FD_SET (clientSocket, &fds);
  struct timeval tv;
  int j =0;
  printf("Cliente enviando\n");
  int sucesso = 0;
  for(int i =0; i<(int)num_pkt; i++) {
      memset(&buffer, 0, sizeof(buffer));
      j= 0;
      tv.tv_sec = 2; //Estabelece o valor de time out de 7 segundos
      tv.tv_usec = 0; //Estabeele o valor de time de 0 milissegundos
      int n = select(clientSocket, &fds, NULL, NULL, &tv);
      //while (n != 0);
      if (i == num_pkt - 1) {
          // *buffer = 's';
          // melhor fazer assim
          buffer[0] = 's';
          buffer[1] = '\0';
          printf("Acabou\n");
      }
      else {
          id = id +1;
          buffer[0] = ((id >> 8) & 0xff);
          buffer[1] = (id & 0xff);
          //buffer[1] = 's';
         // buffer[0] = 's';
          geraPayload(tam_dados, buffer);
          checksum = calculaChecksum(buffer, tam_payload);
          buffer[tam_payload-2] = (uint8_t)((checksum >> 8) & 0xff);
          buffer[tam_payload-1] = (uint8_t)(checksum & 0xff);
      }
      nBytes = strlen(buffer) + 1;

    /* Send message to server */

      sucesso = sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *) &serverAddr, size);
      if(sucesso == (-1)){
          perror("Erro de envio: \n");
      }

    /* Receive message from server */
      //nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);

     //printf("[CLIENT] Received from server: %s\n\n",buffer);

  }

  return 0;
}