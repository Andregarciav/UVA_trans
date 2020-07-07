#ifndef UDP_C_CHECKSUM_H
#define UDP_C_CHECKSUM_H
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

uint16_t calculaChecksum(char* buf, int len);
void avaliador(char *msg, int tam, int *contador);


#endif //UDP_C_CHECKSUM_H
