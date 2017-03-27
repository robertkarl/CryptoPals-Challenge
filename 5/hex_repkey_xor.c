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
	uint8_t *cypher, *raw;
	if (argc != 3)
		usage(argv);
	len = strlen(argv[1]);
	raw = malloc(len / 2);
	cypher = malloc(len / 2);
	hex_to_data(argv[1], (char *)raw);

	repkey_xor(raw, len / 2, cypher, argv[2], strlen(argv[2]));
	printf("%s\n", cypher);
	
	return -1;
}

