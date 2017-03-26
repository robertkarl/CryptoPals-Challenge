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
	char *raw, *out;
	int datalen;
	int blocklen;
	uint8_t *b;

	if (argc != 2)
		usage(argv);
	datalen = 3 * strlen(argv[1]) / 4;
	raw = malloc(datalen);
	if (!raw)
		exit(-1);
	base64_to_data(argv[1], raw);
	printf("Imported %d raw bytes\n", datalen);
	printf("best keysize is %d\n", guess_keysize(raw, datalen));
	b = alloc_transposed_block((uint8_t *)raw, datalen, 1, 2, &blocklen);
	printf("transposed block has %d bytes\n", blocklen);
	out = malloc(2 * blocklen);
	if (!out)
		exit(-1);
	data2hex((char *)b, out, blocklen);
	printf("transposed block:\n");
	printf("%s\n", out);
	free(raw);
	free(out);
	return 0;
}

