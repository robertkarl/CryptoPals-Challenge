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
