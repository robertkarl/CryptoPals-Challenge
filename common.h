/* RK's crypto common functions */

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c);

char integer_to_hexbyte(int);

void hex_to_data(char *in, char *out);

/* Encodes 6 bits to base64. */
char encode64(unsigned c);

/* xor input against xorkey and place into output */
void xor_single(char *input, char *output, char xorkey, unsigned len);
