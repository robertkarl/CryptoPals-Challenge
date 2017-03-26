#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s repkey_xor plaintext rotatingcipher\n", argv[0]);
	exit(-1);
}

void repkey_xor(char *in, int clearlen, char *out, char *key, int keylen)
{
	int i = 0;
	int cypher_index = 0;
	int cypherlen = strlen(key);
	for (i = 0; i < clearlen; i++)
		*out++ = *in++ ^ key[cypher_index++ % cypherlen];
}

int main(int argc, char **argv) {
	
	int len = strlen(argv[1]);
	char *cypher, *coded;
	if (argc != 3)
		usage(argv);
	cypher = malloc(len);
	coded = malloc(2 * len);

	repkey_xor(argv[1], strlen(argv[1]), cypher, argv[2], strlen(argv[2]));
	data2hex(cypher, coded, len);
	printf("%s\n", coded);
	
	return -1;
}

