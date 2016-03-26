#define M 0x00010000

#include<stdio.h>
#include<stdlib.h>


int calculate_checksum(char *block, int block_size);
int process_block(FILE *fp, int block_size);
