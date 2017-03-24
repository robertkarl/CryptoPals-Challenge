#include "common.h"
#include <stdio.h>
#include <assert.h>

static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz0123456789+/";


char encode64(unsigned c) {
	assert(c < 64);
	return base64[c];
}

unsigned hexbytetointeger(char c) {
	if (c < 58)
		return c - 48;
	return c - 97 + 10;
}

char integer_to_hexbyte(int i) {
	if (i < 10)
		return '0' + i;
	return 'a' + i - 10;
}

void hex_to_data(char *in, char*out) {
	unsigned c;
	do {
		c = (hexbytetointeger(*in) << 4) + hexbytetointeger(*(in + 1));
		*out++ = c;
		
	} while (*in++);
}

void xor_single(char *input, char *output, char xorkey, unsigned len)
{
	char c;
	for (int i = 0; i < len; i++) {
		c = *input++;
		*output++ = c ^ xorkey;
	}
}

