#include "Funcoes.h"


void geraPayload(int N, char* msg){
    uint8_t byte = 0;
    time_t semente;
    char *pkt = malloc ((N)*sizeof(char));
    if (!pkt)
        return;
    srand((unsigned) time(&semente));
    for(int i=2; i < N+2 ; i++){
        byte = rand() % (126-33+1)+33; //range da função rand
        while ((byte == '\0')||(byte == '\n')){
            byte = rand() % (126-33+1)+33; //range da função rand
        }
        msg[i]=byte;
    }
}

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
