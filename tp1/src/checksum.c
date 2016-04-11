#define M 0x00010000

#include<stdio.h>
#include<stdlib.h>

#include "checksum.h"

static int calculate_checksum(char *block, int block_size){
    int lower = 0;
    int higher = 0;
    for (int i = 0; i < block_size; i++) {
        lower += block[i];
    }
    lower %= M;
    for (int i = 0; i < block_size; i++) {
        higher += ((block_size - i) * block[i]);
    }
    higher %= M;
    return lower + higher * M;
}

int process_block(FILE *fp, int block_size) {
    int kBlock = block_size;
    char c[kBlock];
    int checksum = -1; 
    int i;

    for (i = 0; i < block_size && !feof(fp); i++) {
        c[i] = fgetc(fp);
    }

    if (i == block_size) {
        checksum = calculate_checksum(c, block_size);
    }

    return checksum;
}
