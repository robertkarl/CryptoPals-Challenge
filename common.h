/* RK's crypto common functions */

#include <stdint.h>

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c);

char integer_to_hexbyte(int);

void hex_to_data(char *in, char *out);
void base64_to_data(uint8_t *in, uint8_t *out);
void data2hex(char *in, char *out, int len);

/* Encodes 6 bits to base64. */
char encode64(unsigned c);
unsigned decode64(char c);

/* xor input against xorkey and place into output */
void xor_single(char *input, char *output, char xorkey, unsigned len);

int score(char *text, int len);

int edit_distance(char *, char *, int len);

void printchars(char *c, int len);
