#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void xor(char *in, char *out, unsigned key) {
	do {
		*out++ = *in++ ^ key;
	} while (*in);
}

int main(int argc, char **argv) {
	char *raw;
	char *xored;
	int len = strlen(argv[1]) / 2;
	int i;

	raw = malloc(len);
	if (!raw)
		exit(-1);
	xored = malloc(len);
	if (!xored)
		exit(-1);
	
	hex_to_data(argv[1], raw);
	for (i = 0; i < 256; i++) {
		xor_single(raw, xored, i, len);
		printf("%d score for %d\n", score(xored, len), i);
	}

	free(raw);
	free(xored);
	return 0;
}
