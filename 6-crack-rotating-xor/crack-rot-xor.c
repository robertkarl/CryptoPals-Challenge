#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_KEYSIZE 40

int guess_keysize(char *in, int len) {
	int i;
	int guess;
	unsigned bestguess = ~0;
	int bestindex = -1;
	char *second;
	for (i = 2; i < MAX_KEYSIZE; i++) {
		second = in + i;
		if (second + i >= in + len)
			return bestindex;
		guess = edit_distance(in, in + i, i);
		if (guess / i < bestguess) {
			printf("score %d at index %d. normalized: %d\n", guess, i, guess / i);
			bestguess = guess / i;
			bestindex = i;
		}
	}
	return bestindex;
}

uint8_t *alloc_transposed_block(uint8_t *in, int inlen, int index, 
	int cipherlen, int *blocklen) {
	uint8_t *ans = malloc(*blocklen);
	uint8_t *c = ans;
	*blocklen = inlen / cipherlen;
	if (!ans)
		return NULL;
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
	char *raw, *out, *xored;
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
	keysize = guess_keysize(raw, datalen);
	printf("best keysize is %d\n", keysize);
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
		printf("best score is %f for xor key %d\n", best, xorkey);
	}
	out = malloc(2 * blocklen);
	if (!out)
		exit(-1);
	data2hex((char *)b, out, blocklen);
	printf("transposed block:\n");
	printf("%s\n", out);
	return 0;
}

