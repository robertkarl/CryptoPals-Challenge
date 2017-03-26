#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void usage(char **argv) {
	printf("usage: %s base64string\n", argv[0]);
	exit(-1);
}	

int main(int argc, char **argv) {
	int len;
	char *raw, *out;
	if (argc != 2)
		usage(argv);
	if (strlen(argv[1]) % 4)
		usage(argv);
 	len = strlen(argv[1]) * 3 / 4;
	raw = malloc(len);
	if (!raw)
		exit(-1);
	out = malloc(2 * len);
	if (!out)
		exit(-1);
	base64_to_data(argv[1], raw);
	data2hex(raw, out, len);
	printf("%s\n", out);
	return -1;
}
