#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_KEYSIZE 40

int guess_keysize(char *in, int len) {
	int i;
	int guess;
	unsigned bestguess = ~0;
	int bestindex = -1;
	char *second;
	for (i = 2; i < MAX_KEYSIZE; i++) {
		second = in + i;
		if (second + i >= in + len)
			return bestindex;
		guess = edit_distance(in, in + i, i);
		if (guess / i < bestguess) {
			printf("score %d at index %d. normalized: %d\n", guess, i, guess / i);
			bestguess = guess / i;
			bestindex = i;
		}
	}
	return bestindex;
}

void usage(char **argv) {
	printf("usage: %s cyphertext\n", argv[0]);
	exit(-1);
}

int main(int argc, char **argv) {
	char *raw;
	int datalen;
	if (argc != 2)
		usage(argv);
	datalen = 3 * strlen(argv[1]) / 4;
	raw = malloc(datalen);
	if (!raw)
		exit(-1);
	base64_to_data(argv[1], raw);
	printf("%d\n", guess_keysize(raw, datalen));
	free(raw);
	return 0;
}

