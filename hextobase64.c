#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*
Three hex characters will become 2 bas64 digits
Group of 3 hex -> integer between [0 and 16**3) -> 2 base64
f6d --> 9t
 */

/* Turn 6 bits of base64 into an ascii char */
char base64word_to_ascii(unsigned c) {
	static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	assert(c < strlen(base64));
	return base64[c];
}

/* turn 16 bits of integer into 2 base64 chars */
void to_base64(unsigned triplet, char *output) {
	unsigned upper = base64word_to_ascii(triplet >> 6);
	unsigned lower = 0;
	/* without the mask, something weird happens (all 1s get shifted in?) i expected a truncation */
	lower = base64word_to_ascii(63 & triplet); 
	*output++ = upper;
	*output = lower;
}

int main(int argc, char **argv) {
	char *input = argv[1];
	unsigned triplet = 0;
	int triplet_offset = 0;
	unsigned c;
	char converted[2];

	while ((c = *input++)) {
		triplet += (hexbytetointeger(c) << (4 * (2 - triplet_offset++)));
		if (triplet_offset >= 3) {
			to_base64(triplet, converted);
			printf("%.2s", converted);
			triplet_offset = 0;
			triplet = 0;
		}
	}
	if (triplet_offset) {
		to_base64(triplet, converted);
		printf("%.2s", converted);
		for (int i = 0; i < 3 - triplet_offset; i++) {
			printf("=");
		}
	}
	printf("\n");
	return 0;
}
