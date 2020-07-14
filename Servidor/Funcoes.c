#include "Funcoes.h"


uint16_t calculaChecksum(char* buf, int len){
    uint32_t sum = 0x0000;
    int i;
    for (i = 0; i < len; i++){
        sum = sum + (uint8_t)buf[i];
    }
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)~sum;
}

int avaliador(char *msg, int tam){
    int checksum_aux = calculaChecksum(msg, tam-2);
    uint8_t c1,c2;
    c1 = msg[tam-2];
    c2 = msg[tam-1];
    int checksum = (c1<<8) | c2;
    if(checksum_aux == checksum){
        return 1;
    }
    else
        return 0;
}
