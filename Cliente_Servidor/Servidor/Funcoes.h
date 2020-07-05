#ifndef UDP_C_CHECKSUM_H
#define UDP_C_CHECKSUM_H
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

uint16_t calculaChecksum(char* buf, int len, uint32_t ip_src, uint32_t ip_dest);
void avaliador(char *msg, int tam, uint32_t ip_src, uint32_t ip_dest, int *contador);


#endif //UDP_C_CHECKSUM_H
