/*
Turn 1 or more hex encoded bytes into base64 encoded data.
*/
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void usage(char **argv) {
	printf("usage: %s [--decode]\n", argv[0]);
	printf("reads arbitrary data from stdin and outputs base64 encoded version to stdout\n");
	printf("if --decode is specified decode from stdin instead\n");
	exit(-1);
}

void write_triplet(FILE *file, unsigned triplet)
{
	int i;
	for (i = 0; i < 3; i++)
		putc(255 & (triplet >> (8 * (2 - i))), file);
}

void base64_to_data(char *in, FILE *file)
{
	/* four bytes of input is 4 base64 chars. that's 24 bits of out */
	char *c = in;
	unsigned decoded = 0;
	while (*c) {
		decoded <<= 6;
		if (*c != '=') {
			decoded |= decode64(*c);
		}
		c++;
		if ((c - in) % 4 == 0) {
			write_triplet(file, decoded);
		}
	}
}

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

void encode(FILE *in, FILE *out) {

	unsigned septet = 0;
	int triplet_offset = 0;
	int c;
	char encoded[4];

	while ((c = fgetc(stdin)) != EOF) {
		unsigned bitoffset = 8 * (2 - triplet_offset++);
		septet += c << bitoffset;
		if (triplet_offset >= 3) {
			to_base64(septet, encoded, 24);
			printf("%.4s", encoded);
			triplet_offset = 0;
			septet = 0;
		}
	}
	if (triplet_offset) {
		to_base64(septet, encoded, 8 * triplet_offset); /* todo: this is a guess */
		printf("%.4s", encoded);
	}
	printf("\n");

}

void decode(FILE *in, FILE *out) {
	/* read four bytes, then use print_triplet to spit out 3 bytes */
	int c;
	int quartet_index = 0;
	char quartet[5];
	quartet[4] = 0;
	while ((c = getc(in)) != EOF) {
		if (c == ' ' || c == '\n')
			continue;
		quartet[quartet_index++] = c;
		if (quartet_index == 4) {
			base64_to_data(quartet, out);
			quartet_index = 0;
		}
	}
	assert(quartet_index == 0);
}

int main(int argc, char **argv) {
	switch (argc) {
	case 1:
		encode(stdin, stdout);
		break;
	case 2:
		if (strcmp(argv[1], "--decode"))
			usage(argv);
		decode(stdin, stdout);
		break;
	default:
		usage(argv);
	}
	return 0;
}

