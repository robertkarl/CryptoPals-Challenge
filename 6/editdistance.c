#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s string1 string2\n", argv[0]);
	printf("requires two args of the same length\n");
	exit(-1);
}

int main(int argc, char **argv) {
	char *in1, *in2;
	int len;
	if (argc != 3)
		usage(argv);
	in1 = argv[1];
	in2 = argv[2];
	len = strlen(in1);
	if (len != strlen(in2))
		usage(argv);
	printf("%d\n", edit_distance(in1, in2, len));
	return 0;
}
