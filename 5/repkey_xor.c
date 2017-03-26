#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void repkey_xor(char *in, int clearlen, char *out, char *key, int keylen)
{
	int i = 0;
	int cypher_index = 0;
	int cypherlen = strlen(key);
	for (i = 0; i < len; i++)
		*out++ = *in++ ^ key[cypher_index++ % cypherlen];
}

int main(int argc, char **argv) {
	int len = strlen(argv[1]);
	char *cypher = malloc(len);
	char *coded = malloc(2 * len);

	repkey_xor(argv[1], cypher, "ICE", len);
	data2hex(cypher, coded, len);
	printf("%s\n", coded);
	
	return -1;
}

