#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char **argv) {
	char *raw = 0;
	char *xored = 0;
	int len = strlen(argv[1]) / 2;
	int xorkey = atoi(argv[2]);
	int i;

	raw = malloc(len);
	xored = malloc(len);

	hex_to_data(argv[1], raw);
	
	xor_single(raw, xored, xorkey, len);
	for (i = 0; i < len; i++) {
		printf("%c", xored[i]);
	}
	printf("\n");
	return 0;
}
