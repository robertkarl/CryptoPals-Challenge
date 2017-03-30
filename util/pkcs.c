#include <stdio.h>
#include <stdlib.h>

void usage(char **argv) {
	printf("usage: %s <block size>\n", argv[0]);
	printf("reads arbitrary data from stdin emits it with padding to size\n");
	exit(-1);
}

int main(int argc, char **argv) {
	int i = 0;
	int c;
	int blocklen;
	int padding;

	if (argc != 2)
		usage(argv);

	i = 0;
	blocklen = atoi(argv[1]);

	while ((c = getc(stdin)) != EOF) {
		putc(c, stdout);
		i++;
	}

	if (i % blocklen) {
		padding = blocklen - (i % blocklen);
		i = padding;
		while (i--)
			putc(padding, stdout);
	}
	return 0;
}

