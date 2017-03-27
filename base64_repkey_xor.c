#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s base64 rotatingcipher\n", argv[0]);
	exit(-1);
}

void repkey_xor(uint8_t *in, int clearlen, uint8_t *out, char *key, int keylen)
{
	int i = 0;
	int cypher_index = 0;
	int cypherlen = strlen(key);
	for (i = 0; i < clearlen; i++)
		*out++ = *in++ ^ key[cypher_index++ % cypherlen];
}

int main(int argc, char **argv) {
	int len;
	uint8_t *raw, *cypher;
	int rawlen;
	int i;

	if (argc != 3)
		usage(argv);
	len = strlen(argv[1]);

	rawlen = 3 * len / 4;
	raw = malloc(rawlen);
	cypher = malloc(rawlen);
	base64_to_data(argv[1], raw);
	repkey_xor(raw, rawlen, cypher, "ioiio", 5);
	for (i = 0; i < rawlen; i++)
		printf("%c", cypher[i]);
	return -1;
}

