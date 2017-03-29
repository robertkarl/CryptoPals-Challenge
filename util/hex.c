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

void hex2data(FILE *in, FILE *out) {
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

void encode(FILE *in, FILE *out) {

}

int main(int argc, char **argv) {
	switch (argc) {
	case 1:
		encode(stdin, stdout);
		break;
	case 2:
		if (strcmp(argv[1], "--decode"))
			usage(argv);
		hex2data(stdin, stdout);
		break;
	default:
		usage(argv);
	}
	return 0;
}

