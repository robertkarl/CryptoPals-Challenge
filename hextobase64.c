#include <stdio.h>
#include <assert.h>

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c) {
	if (c < 58)
		return c - 48;
	return c - 65 + 10;
}

int main(int argc, char ** argv) {
	printf("%d", (unsigned)hexbytetointeger(argv[1][0]));
	char *in = argv[1];
	while (

	return -1;
}
