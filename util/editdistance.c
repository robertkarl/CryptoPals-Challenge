#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s str1 str2\n", argv[0]);
	printf("strings must be same length\n");
	exit(-1);
}

int main(int argc, char **argv) {
	char *a, *b;
	if (argc != 3)
		usage(argv);
	a = argv[1];
	b = argv[2];
	printf("a has length %d and b has length %d\n", strlen(a), strlen(b));
	if (strlen(a) != strlen(b))
		usage(argv);
	printf("%d\n", edit_distance(a, b, strlen(a)));
	exit(-1);
}

