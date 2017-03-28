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
	uint8_t *cypher, *coded;
	if (argc != 3)
		usage(argv);
	len = strlen(argv[1]);
	cypher = malloc(len);
	coded = malloc(2 * len);

	repkey_xor((uint8_t *)argv[1], strlen(argv[1]), cypher, argv[2], strlen(argv[2]));
	data2hex((char *)cypher, (char *)coded, len);
	printf("%s\n", coded);
	
	return -1;
}

