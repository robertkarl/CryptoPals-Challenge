#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char **argv) {
	char *raw = 0;
	char *xored = 0;
	int len = strlen(argv[1]) / 2;

	raw = malloc(len);
	if (!raw)
		exit(-1);
	xored = malloc(len);
	if (!xored)
		exit(-1);
	
	hex_to_data(argv[1], raw);
	xor_single(raw, xored, atoi(argv[2]), len);
	for (int i = 0; i < len; i++)
		printf("%c", xored[i]);
	printf("\n");

	free(xored);
	free(raw);
	return 0;
}
