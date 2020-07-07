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
void avaliador(char *msg, int tam, int *contador){
    int a=0;
    while(a<tam){
        a++;
    }
    int id, checksum, checksum_aux1;
    int i=0;
    char vec_aux_id[5], vec_aux_check[5];
    char *ret;
    while(msg[i]!='F'){ //salva todos os valores até o primeiro marcador F
        vec_aux_id[i]=msg[i];
        i++;
    }
    id = strtol(vec_aux_id,&ret,10);
    i=i+1; //começar a iterar sobre msg depois de F
    while(msg[i]!='F'){
        i++;
    }
    int j;
    //aqui calculamos onde precisamos andar no vetor msg para conseguir o valor de checksum dele
    if(id<10){
        i=i+1;
        checksum_aux1 = calculaChecksum(msg, (tam-9)); //calculo da checksum para integridade, ignorando o valor do campo checksum
        for(j=0;j<5;j++){
            vec_aux_check[j]=msg[i];
            i++;
        }}
    else if(id<100&&id>=10){
        i=i+1;
        checksum_aux1 = calculaChecksum(msg, (tam-8));
        for(j=0;j<5;j++){
            vec_aux_check[j]=msg[i];
            i++;
        }}
    else if(id<1000&&id>=100){
        i=i+1;
        checksum_aux1 = calculaChecksum(msg, (tam-7));
        for(j=0;j<5;j++){
            vec_aux_check[j]=msg[i];
            i++;
        }}
    else if(id<10000&&id>=1000){
        i=i+1;
        checksum_aux1 = calculaChecksum(msg, (tam-6));
        for(j=0;j<5;j++){
            vec_aux_check[j]=msg[i];
            i++;
        }}
    else{
        i=i+1;
        checksum_aux1 = calculaChecksum(msg, (tam-5));
        for(j=0;j<5;j++){
            vec_aux_check[j]=msg[i];
            i++;
        }}
    checksum = strtol(vec_aux_check, &ret, 10);
    if(checksum==checksum_aux1){
        *contador= *contador + 1;
    }
    printf("\nContador: %d\n", *contador);
}
