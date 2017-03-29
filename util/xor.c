#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(char **argv) {
	printf("usage: %s cipher\n", argv[0]);
	printf("read from stdin and cyclically apply cipher with xor to the plaintext.\n");
	exit(-1);
}

int main(int argc, char **argv) {
	int c;
	int cipher_i = 0;
	FILE *in = stdin;
	FILE *out = stdout;
	char *key;
	unsigned keylen;

	if (argc != 2)
		usage(argv);

	key = argv[1];
	keylen = strlen(key);
	while ((c = getc(in)) != EOF)
		putc(c ^ key[cipher_i++ % keylen], out);

	return 0;
}

