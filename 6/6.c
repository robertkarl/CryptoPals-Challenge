#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_KEYSIZE 40

int guess_keysize(char *in) {
	int i;
	int guess;
	int bestguess = 1 << 30;
	int bestindex = -1;
	for (i = 2; i < MAX_KEYSIZE; i++) {
		guess = edit_distance(in, in + i, i);
		if (guess / i < bestguess) {
			printf("found a better score of %d at index %d. normalized: %d\n", guess, i, guess / i);
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
	if (argc != 2)
		usage(argv);
	raw = malloc(strlen(argv[1]) / 2);
	if (!raw)
		exit(-1);
	hex_to_data(argv[1], raw);
	printf("%d\n", guess_keysize(raw));
	return -1;
}

