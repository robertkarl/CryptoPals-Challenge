#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define NCHARS 60

void printchars(char *c, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%c", c[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	FILE *f = fopen(argv[1], "r");
	char chars[NCHARS + 1];
	char raw[NCHARS / 2];
	char xored[NCHARS / 2];
	int s;
	int i = 0;
	int j;

	if (!f)
		exit(-1);

	while (fgets(chars, NCHARS + 1, f)) {
		chars[NCHARS] = 0; /* it was previously a newline */
		hex_to_data(chars, raw);
		i++;
		for (j = 0; j < 256; j++) {
			xor_single(raw, xored, j, NCHARS / 2);
			s = score(xored, NCHARS / 2);
			if (s < 400) {
				printchars(xored, NCHARS / 2);
				printf("%s\n", chars);
				printf("%03d with key %d at file index %d\n",
					s, j, i);
			}
		}
	}
	return -1;
}

