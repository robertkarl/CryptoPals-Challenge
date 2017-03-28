#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void usage(char **argv) {
	printf("%s: xor two buffers of equal length\n", argv[0]);
	exit(-1);
}

int main(int argc, char **argv) {
	char *a;
	char *b;
	if (argc != 3) {
		usage(argv);
	}
	a = argv[1];
	b = argv[2];
	if (strlen(argv[1]) != strlen(argv[2]))
		usage(argv);
	do {
		unsigned outval = hexbytetointeger(*a++) ^ hexbytetointeger(*b++);
		printf("%c", int2hex(outval));
	} while (*a);
	printf("\n");
	return 0;
}
