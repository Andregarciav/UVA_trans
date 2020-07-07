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

// Gera string de tamanho N só com caracteres imprimíveis
char *geraPayload(int N){
    uint8_t byte = 0;
    time_t semente;
    char *pkt = malloc ((N)*sizeof(char));
    if (!pkt)
        return NULL;
    srand((unsigned) time(&semente));
    pkt[0] = 'F';
    for(int i=1; i < N ; i++){
        byte = rand() % (126-33+1)+33; //range da função rand
        while ((byte == '\0')||(byte == '\n')||(byte=='F')){// F será o marcador pra saber quando acaba payload e começa checksum
            byte = rand() % (126-33+1)+33; //range da função rand
        }
        pkt[i]=byte;
    }
    pkt[N-1]='F';
    return pkt;
}
