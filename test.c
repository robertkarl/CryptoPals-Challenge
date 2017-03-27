#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "common.h"

#define _64TESTDATA "I0mL"

void test_base64_to_data() {
	char sample[13];
	char out[13] = {35, 69, 139};

	strcpy(sample, _64TESTDATA);
	base64_to_data(sample, out);
	assert(*out == 35);
	assert(*(out + 1) == 73);
	printf("%d\n", *(out + 2));
	printf("writing 139 to it\n");
	assert(*(out + 2) == (char)139);

}

int main(int argc, char **argv) {
	test_base64_to_data();
	return 0;
}
