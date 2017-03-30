#include <stdio.h>
#include <stdint.h>

#include "aes.h"

#define BLOCKSIZE 16

void decrypt(uint8_t *block, uint8_t *lastblock) {


}

int main(int argc, char **argv) {

	uint8_t data[2 * BLOCKSIZE];

	uint8_t *block = data;
	uint8_t *lastblock = data + BLOCKSIZE;
	uint8_t *tmp;
	uint8_t *curr = block;
	int c;
	FILE *f = stdin;
	

	while ((c = getc(f)) != EOF) {
		*curr++ = c;
		if (curr - block == BLOCKSIZE) {
			decrypt(block, lastblock);

			tmp = lastblock;
			lastblock = block;
			block = tmp;
			
			curr = block;
		}
	}
		
	return 0;
}
