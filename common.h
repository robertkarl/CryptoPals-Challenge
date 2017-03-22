/* RK's crypto common functions */

/* @arg c a printable hex character (one of [0..F])
returns the integer value of that char if it's a valid char,
garbage otherwise.
*/
unsigned hexbytetointeger(char c);
char integer_to_hexbyte(int);
