#include "common.h"
#include <stdio.h>
unsigned hexbytetointeger(char c) {
	if (c < 58)
		return c - 48;
	return c - 97 + 10;
}

char integer_to_hexbyte(int i) {
	if (i < 10)
		return '0' + i;
	return 'a' + i;
}

void hex_to_ascii(char *in, char*out) {
	unsigned c;
	do {
		printf("converted first byte to int. got %u\n", hexbytetointeger(*in));
		c = hexbytetointeger(*in) << 4 + hexbytetointeger(*(in + 1));
		*out++ = c;
		
	} while (*in++);
}

