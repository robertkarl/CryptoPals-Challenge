#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aes.h"

void usage(char **argv) {
	printf("usage: %s key\n", argv[0]);
	printf("decrypts from stdin to stdout using aes ecb 128\n");
	exit(-1);
}

int main(int argc, char **argv) {
	uint8_t *key = (uint8_t *)argv[1];
	uint8_t *out;
	int inlen;
	uint8_t in[4000];
	int i = 0;
	int c;
	out = malloc(16);

	if (argc != 2)
		usage(argv);
	if (strlen(argv[1]) != 16)
		usage(argv);

	while ((c = getc(stdin)) != EOF) {
		in[i++] = c;
	}
	inlen = i;

	i = 0;
	while (i < inlen) {
		AES128_ECB_decrypt((uint8_t *)in + i, key, (uint8_t *)out); 
		printf("%.16s", out);
		i += 16;
	}
	return 0;
}
