#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define NCHARS 60

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

	while (fgets(chars, NCHARS + 2, f)) {
		chars[NCHARS] = 0; /* it was previously a newline */
		hex_to_data(chars, raw);
		i++;
		for (j = 0; j < 256; j++) {
			xor_single(raw, xored, j, NCHARS / 2);
			s = score(xored, NCHARS / 2);
			if (s < 700) {
				printchars(xored, NCHARS / 2 - 1);
				printf(" (score is %f at index %d)\n",
					((float)s) / NCHARS,
					i);
			}
		}
	}
	return -1;
}

