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
	uint8_t *curr;
	uint8_t in[2000];
	int i = 0;
	int c;
	printf("%d args\n", argc);
	if (argc != 2)
		usage(argv);

	while ((c = getc(stdin)) != EOF) {
		in[i++] = c;
	}
	out = malloc(17);
	curr = in;
	while (curr - in < i) {
		AES128_ECB_decrypt((uint8_t *)curr, key, (uint8_t *)out); 
		printf("%.16s", out);
		curr += 16;
	}
	return 0;
}
