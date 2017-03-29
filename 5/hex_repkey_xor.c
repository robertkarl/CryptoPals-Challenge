#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s plaintext rotatingcipher\n", argv[0]);
	exit(-1);
}

int main(int argc, char **argv) {
	int len;
	uint8_t *output;

	if (argc != 3)
		usage(argv);

	len = strlen(argv[1]);
	output = malloc(len / 2);
	repkey_xor((uint8_t *)argv[1], len, output, argv[2], strlen(argv[2]));
	printf("%s\n", output);
	
	return -1;
}

