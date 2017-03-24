#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*
Three hex characters will become 2 base64 digits
Group of 3 hex -> integer between [0 and 16**3) -> 2 base64
f6d --> 9t
 */

/* Turn 6 bits of base64 into an ascii char */
char base64word_to_ascii(unsigned c) {
	static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";
	assert(c < strlen(base64));
	return base64[c];
}

/* turn up to 24 bits of integer into base64 chars */
void to_base64(unsigned triplet, char *output, int inbits) {
	assert(inbits <= 24 && inbits > 0 && (inbits % 8 == 0));
	unsigned end_equals = 4;
	unsigned sixbitmask = 63;
	while (inbits > 0) {
		inbits -= 6;
		unsigned c = base64word_to_ascii(triplet & sixbitmask);
		triplet >>= 6;
		*(output-- + 3) = c;
		end_equals--;
	}
	for (int i = 0; i < end_equals; i++) {
		*(output + 4 + end_equals) = '=';
		output++;
	}
}

int main(int argc, char **argv) {
	char *input = argv[1];
	unsigned septet = 0;
	int triplet_offset = 0;
	unsigned c;
	char converted[4];

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
