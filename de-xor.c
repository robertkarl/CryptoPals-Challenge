#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int char_in_set(char c, char *charset) {
	char *curr = charset;
	do {
		if (*curr == c) {
			return 1;
		}
	} while (*(++curr));
	return 0;
}

int isvowel(char c) {
	char *vowels = "aeiou";
	return char_in_set(c, vowels);
}

int israre(char c) {
	char *cs = "zqkwjx";
	return char_in_set(c, cs);
}

void xor(char *in, char *out, unsigned key) {
	do {
		*out++ = *in++ ^ key;
	} while (*in);
}
	

int score(char *text) {
	char *curr = text;
	char c;
	int score;
	while ((c = *curr++)) {
		if (isvowel(c))
			continue;
		if (israre(c))
			score += 10;
		else
			score += 5;
	}
	return score;
}

int main(int argc, char **argv) {
	printf("%d\n", score(argv[1]));
	char *out = malloc(strlen(argv[1]));
	if (!out)
		exit(-1);
	xor(argv[1], out, 0);
	printf("xored with 0: %s\n", out);
	char *asciified = malloc(strlen(argv[1]) / 2);
	if (!asciified)
		exit(-1);
	hex_to_ascii(out, asciified);
	printf("%s\n", asciified);
	

	free(out);
	free(asciified);
	return 0;
}
