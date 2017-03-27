#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_KEYSIZE 40

int guess_keysize(char *in, int len) {
	int i;
	int d1;
	float guess;
	float bestguess = 1e6;
	int bestindex = -1;
	for (i = 2; i < MAX_KEYSIZE; i++) {
		d1 = edit_distance(in, in + i, i);
		guess = ((float)d1)/ i;
		printf("distance %d at index %d. normalized: %f\n", d1, i, guess);
		if (guess < bestguess) {
			bestguess = guess;
			bestindex = i;
		}
	}
	return bestindex;
}

uint8_t *alloc_transposed_block(uint8_t *in, int inlen, int index, 
	int cipherlen, int *blocklen) {
	uint8_t *ans, *c;

	*blocklen = inlen / cipherlen;
	ans = malloc(*blocklen);
	if (!ans)
		return NULL;

	c = ans;
	while (c < ans + *blocklen) {
		*c++ = *(in + index);
		in += cipherlen;
	}
	return ans;

}

void usage(char **argv) {
	printf("usage: %s cyphertext\n", argv[0]);
	exit(-1);
}

int main(int argc, char **argv) {
	char *xored;
	uint8_t *raw;
	int datalen;
	int blocklen;
	uint8_t *b;
	int i, j;
	int keysize;
	float s;
	float best;
	char xorkey = 0;

	if (argc != 2)
		usage(argv);
	datalen = 3 * strlen(argv[1]) / 4;
	raw = malloc(datalen);
	if (!raw)
		exit(-1);
	base64_to_data(argv[1], raw);
	printf("Imported %d raw bytes\n", datalen);
	keysize = guess_keysize((char *)raw, datalen);
	printf("best keysize found is %d\n", keysize);
	printf("key sequence is ");
	for (i = 0; i < keysize; i++) {
		b = alloc_transposed_block((uint8_t *)raw, datalen, i, keysize, &blocklen);
		xored = malloc(blocklen);
		best = 1e6;
		for (j = 0; j < 256; j++) {
			xor_single((char *)b, xored, j, blocklen);
			s = ((float)score(xored, blocklen)) / blocklen;
			if (s < best) {
				best = s;
				xorkey = j;
			}
		}
		printf("%c", xorkey);
	}
	printf("\n");
	return 0;
}

