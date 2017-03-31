#include "common.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz0123456789+/";

void printchars(uint8_t *c, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%c", c[i]);
	}
}

void repkey_xor(uint8_t *in, int clearlen, uint8_t *out, char *key, int keylen)
{
	int i;
	int cypher_index = 0;
	for (i = 0; i < clearlen; i++)
		*out++ = *in++ ^ key[cypher_index++ % keylen];
}

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


char encode64(unsigned c) {
	assert(c < 64);
	return base64[c];
}

unsigned hexbytetointeger(char c) {
	if (c < 58)
		return c - 48;
	return c - 97 + 10;
}

unsigned decode64(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	else if (c >= 'a' && c <= 'z')
		return 26 + c - 'a';
	else if (c >= '0' && c <= '9')
		return 52 + c - '0';
	else if (c == '+')
		return 62;
	return 63;
}

char int2hex(int i) {
	if (i < 10)
		return '0' + i;
	return 'a' + i - 10;
}

void hex_to_data(char *in, char *out) {
	unsigned c;
	while (*in) {
		unsigned upper = (hexbytetointeger(*in) << 4);
		unsigned lower = hexbytetointeger(*(in + 1));
		c = upper + lower;
		*out++ = c;
		in += 2;
	}
}

void data2hex(char *in, char*out, int inlen) {
	int i = 0;
	while (i++ < inlen) {
		unsigned char cbyte = *in++;
		*out++ = int2hex(cbyte >> 4);
		*out++ = int2hex(cbyte & 15);
	}
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

void xor_single(char *input, char *output, char xorkey, unsigned len)
{
	char c;
	int i;
	for (i = 0; i < len; i++) {
		c = *input++;
		*output++ = c ^ xorkey;
	}
}

int edit_distance(char *a, char *b, int len)
{
	int i;
	unsigned v;
	int diff = 0;
	while (len--) {
		v = a[len] ^ b[len];
		for (i = 0; i < 8; i++) {
			if (v & 1)
				diff++;
			v >>= 1;
		}
			
	}
	return diff;
}

void xor_buffers(uint8_t *a, uint8_t *b, uint8_t *out, int len) {
	int c;
	while (len--) {
		c = *a++ ^ *b++;
		*out++ = c;
	}
}

