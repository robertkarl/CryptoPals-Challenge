/*
AES CBC implementation. Uses AES ECB impl included
*/
#include "common.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CBC 0
#include "aes.h"

#define BLOCKSIZE 16

void usage(char **argv) {
	printf("usage: %s <key>\n", argv[0]);
	printf("AES CBC decrypt chars from input to output using <key>\n");
	printf("key must be an ASCII string, passable in shell\n");
	exit(-1);
}

void decrypt(uint8_t *block, uint8_t *lastblock, uint8_t *key) {
	uint8_t out[BLOCKSIZE];
	AES128_ECB_decrypt(block, key, out);
	xor_buffers(lastblock, out, out, BLOCKSIZE);
	printchars(out, BLOCKSIZE);
}

int main(int argc, char **argv) {

	uint8_t *block, *lastblock, *tmp, *key;
	int i = 0;
	int c;
	FILE *f = stdin;
	lastblock = calloc(BLOCKSIZE, 1); /* effectively an IV of 0's */
	block = calloc(BLOCKSIZE, 1);

	if (!block || !lastblock)
		exit(-1);
	if (argc != 2)
		usage(argv);
	key = (uint8_t *)(argv[1]);
	

	while ((c = getc(f)) != EOF) {
		*(block + i++) = c;
		if (i == BLOCKSIZE) {
			decrypt(block, lastblock, key);

			/* swap last and curr block pointers */
			tmp = lastblock;
			lastblock = block;
			block = tmp;
			
			i = 0;
		}
	}
		
	return 0;
}
