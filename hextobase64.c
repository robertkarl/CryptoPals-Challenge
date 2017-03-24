/*
Turn 1 or more hex encoded bytes into base64 encoded data.
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
/*
Encode 24 bit chunks of integer into base64.
invariant: 4 base64 bytes should be written to output sequentially.
*/
void to_base64(unsigned triplet, char *output, int inbits) {
	char *end = output + 4;
	unsigned sixbitmask = 63;
	int shift = 18; 
	unsigned c;

	assert(inbits <= 24 && inbits > 0 && (inbits % 8 == 0));
	while (inbits > 0) {
		inbits -= 6;
		c = encode64(
			(triplet >> shift) & sixbitmask);
		*(output++) = c;
		shift -= 6;
	}
	while (output < end)
		*output++ = '=';
}

void usage(char **argv) {
	printf("usage: %s hexdata\n", argv[0]);
	printf("input must be 1 or more bytes hex encoded\n");
	exit(-1);
}

int main(int argc, char **argv) {
	char *input;
	int inlen;
	unsigned septet = 0;
	int triplet_offset = 0;
	unsigned c;
	char converted[4];

	if (argc != 2)
		usage(argv);
	input = argv[1];
	inlen = strlen(input);
	if (inlen % 2)
		usage(argv);

	while ((c = *input++)) {
		unsigned bitoffset = 4 * (5 - triplet_offset++);
		septet += (hexbytetointeger(c) << bitoffset);
		if (triplet_offset >= 6) {
			to_base64(septet, converted, 24);
			printf("%.4s", converted);
			triplet_offset = 0;
			septet = 0;
		}
	}
	if (triplet_offset) {
		to_base64(septet, converted, 8 * (triplet_offset / 2));
		printf("%.4s", converted);
	}
	printf("\n");
	return 0;
}
