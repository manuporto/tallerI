#define M 0x00010000
int calculate_checksum(char *block, int block_size){
	int lower = 0;
	int higher = 0;
	for(int i = 0; i < block_size; i++) lower += block[i];	
	lower %= M;

	for(int i = 0; i < block_size; i++) higher += ((block_size - i) * block[i]);	
	higher %= M;

	return lower + higher * M;
}
