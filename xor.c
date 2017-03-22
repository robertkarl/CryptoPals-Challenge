#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("%s: xor two buffers of equal length\n", argv[0]);
		exit(-1);
	}
	char *a = argv[1];
	char *b = argv[2];
	if (strlen(argv[1]) != strlen(argv[2]))
		exit(-1);
	do {
		unsigned outval = hexbytetointeger(*a++) ^ hexbytetointeger(*b++);
		printf("%c", integer_to_hexbyte(outval));
	} while (*a);
	printf("\n");
	return 0;
}
