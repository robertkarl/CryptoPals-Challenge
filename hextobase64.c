#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
Three hex characters will become 2 bas64 digits
Group of 3 hex -> integer between [0 and 16**3) -> 2 base64
f6d --> 9t
 */

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c) {
	if (c < 58)
		return c - 48;
	return c - 97 + 10;
}

/* Turn 6 bits of base64 into an ascii char */
char base64word_to_ascii(char c) {
	if (c < 26)
		return 'A' + c;
	if (c < 52)
		return 'a' + c - 26;
	if (c < 62)
		return '0' + c - 52;
	if (c == 62)
		return '+';
	return '/';
}

/* turn 16 bits of integer into 2 base64 chars */
void to_base64(unsigned triplet, char *output) {
	printf("shifted looks like %d\n", triplet >> 6);
	*output++ = base64word_to_ascii(triplet >> 6);	
	*output = base64word_to_ascii(triplet); /* hopefiully this truncates?? */
}

int main(int argc, char **argv) {
	char *input = argv[1];
	int len = strlen(input);
	if (len % 3) {
		printf("pad front with zeros bitch\n");
		exit(-1);
	}
	unsigned triplet = 0;
	int triplet_offset = 0;
	unsigned c;

	while (c = *input++) {
		triplet += (hexbytetointeger(c) << (4 * (2 - triplet_offset++)));
		if (triplet_offset >= 3) {
			printf("triplet converted with value %d\n", triplet);
			triplet_offset = 0;
			triplet = 0;
		}
	}

	char *bas64;
	strcpy(bas64, "  ");
	char *bin = argv[2];
	to_base64(atoi(bin), bas64);
	printf("base64 output of %d is %s\n", atoi(bin), bas64);

	return 0;
}
