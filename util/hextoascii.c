/*
Turn 1 or more hex encoded bytes into base64 encoded data.
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

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
	unsigned c, d;
	char converted[4];

	if (argc != 2)
		usage(argv);
	input = argv[1];
	inlen = strlen(input);
	if (inlen % 2)
		usage(argv);

	while (*input) {
		c = hexbytetointeger(*input++);
		d = hexbytetointeger(*input++);
		printf("%c", (c << 4) + d);
	}
	printf("\n");
	return 0;
}
