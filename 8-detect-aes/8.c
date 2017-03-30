#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char **argv) {
	printf("usage: %s <file containing lines of hex data \n", argv[0]);
	exit(-1);
}

int checkblock(char *a, char *b, int blocksize) {
	int i;
	for (i = 0; i < blocksize; i++) {
		if (*(a + i) != *(b + i))
			return 0;
	}
	return 1;
}
int checkline(char *line, int len) {
	/* return nonzero if the line contains two 16 byte sequences (32 hex chars) that are identical */
	int blocksize = 32;
	char *c = line;
	char *o = c + blocksize;
	assert(len % blocksize == 0);
	while (c < line + len) {
		if (checkblock(c, o, blocksize))
			return 1;
		o += blocksize;
		if (o >= line + len) {
			c += blocksize;
			o = c + blocksize;
		}
	}
	return 0;
}

void printchars(char *a, int len) {
	int i;
	for (i = 0; i < len; i++)
		putc(a[i], stdout);
}

int main(int argc, char **argv) {
	char line[400];
	char *lp = line;
	FILE *f;
	int c;
	int lines_differ = 0;

	char *containsdupe = 
		"1234567890abcdef1234567890abcdef"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"1234567890abcdef1234567890abcdef";
	if (argc != 2)
		usage(argv);

	f = fopen(argv[1], "r");
	assert(checkline(containsdupe, strlen(containsdupe)));
	while ((c = getc(f)) != EOF) {
		if (c == '\n') {
			lines_differ = checkline(line, lp - line);
			if (lines_differ)
				printchars(line, lp - line);
			lp = line;
		}
		else 
			*lp++ = c;
	}
	return 0;
}
