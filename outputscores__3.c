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

int lookslikeenglish(char c) {
	char *cs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	return char_in_set(c, cs);
}

void xor(char *in, char *out, unsigned key) {
	do {
		*out++ = *in++ ^ key;
	} while (*in);
}

int score(char *text, int len) {
	char *curr = text;
	char c;
	int score = 0;
	int i;
	for (i = 0; i < len; i++) {
		c = *curr++;
		if (isvowel(c))
			continue;
		if (israre(c))
			score += 10;
		else if (lookslikeenglish(c))
			score += 5;
		else
			score += 100;
	}
	return score;
}

int main(int argc, char **argv) {
	char *raw;
	char *xored;
	int len = strlen(argv[1]) / 2;
	int i;

	raw = malloc(len);
	if (!raw)
		exit(-1);
	xored = malloc(len);
	if (!xored)
		exit(-1);
	
	hex_to_data(argv[1], raw);
	for (i = 0; i < 256; i++) {
		xor_single(raw, xored, i, len);
		printf("%d score for %d\n", score(xored, len), i);
	}

	free(raw);
	free(xored);
	return 0;
}
