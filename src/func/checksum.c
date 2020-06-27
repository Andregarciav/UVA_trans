#include "checksum.h"
#include <inttypes.h>
#include <unistd.h>

uint32_t calculaChecksum(char* buf, int len){
    	uint32_t sum = 0x0000;
	int i;
	for (i = 0; i < len; i++){
		sum = sum + (uint8_t)buf[i];
	}
	return sum;
}