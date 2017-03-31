/* RK's crypto common functions */

#include <stdint.h>

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c);

void repkey_xor(uint8_t *in, int clearlen, uint8_t *out, char *key, int keylen);

char int2hex(int);

void hex_to_data(char *in, char *out);
void data2hex(char *in, char *out, int len);

/* Encodes 6 bits to base64. */
char encode64(unsigned c);
unsigned decode64(char c);

/* xor input against xorkey and place into output */
void xor_single(char *input, char *output, char xorkey, unsigned len);

/* Read a byte from a and b, then xor them and place in out */
void xor_buffers(uint8_t *a, uint8_t *b, uint8_t *out, int len);

int score(char *text, int len);

int edit_distance(char *, char *, int len);

void printchars(uint8_t *c, int len);
