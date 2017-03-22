#include <stdio.h>
#include <assert.h>
#include <string.h>

/*
Three hex characters will become 2 bas64 digits
Group of 3 hex -> integer between [0 and 16**3) -> 2 base64
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

int main(int argc, char ** argv) {
	char *input = argv[1];
	int len = strlen(argv[1]);
	int word_as_int = 0;
	char *word = input + len - 1;

	printf("input is %s, or %d. maps to %d\n", argv[1], input[0], hexbytetointeger(input[0]));
	int which_triplet = 0;
	while (word >= input) {
		unsigned v = hexbytetointeger(*word);
		word_as_int += (v << 4 * (which_triplet++));
		if (which_triplet == 3) {
			printf("converted triplet to integer: %d\n", word_as_int);
			word_as_int = 0;
			which_triplet = 0;
		}
		word--;
	}

	return -1;
}
