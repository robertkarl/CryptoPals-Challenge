#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void usage(char **argv) {
	printf("usage: %s [--decode]\n", argv[0]);
	printf("reads arbitrary data from stdin and outputs hex encoded version to stdout\n");
	printf("if --decode is specified input must be hex data\n");
}

void decode_hex(FILE *in, FILE *out) {
	int first, second;
	unsigned c, upper, lower;
	while ((first = getc(in)) != EOF) {
		second = getc(in);
		assert(second != EOF);
		upper = hexbytetointeger(first) << 4;
		lower = hexbytetointeger(second);
		c = upper + lower;
		putc(c, out);
	}
}

void encode_hex(FILE *in, FILE *out) {
	int c;
	while ((c = getc(in)) != EOF) {
		putc(int2hex(c >> 4), out);
		putc(int2hex(c & 15), out);
	}
}

int main(int argc, char **argv) {
	switch (argc) {
	case 1:
		encode_hex(stdin, stdout);
		break;
	case 2:
		if (strcmp(argv[1], "--decode"))
			usage(argv);
		decode_hex(stdin, stdout);
		break;
	default:
		usage(argv);
	}
	return 0;
}

