CC=gcc
CFLAGS = -I. -Wstrict-prototypes -Wall -g -pedantic -ansi
DEPS = common.h

all: xor base64_repkey_xor base64tohex hextobase64 xorchar repkey_xor hex_repkey_xor editdistance hextoascii crack-rot-xor find_xor_key b64

xor: xor.c common.o
	$(CC) -o xor $(CFLAGS) xor.c common.o

xorchar: xorchar.c common.o
	$(CC) -o xorchar $(CFLAGS) xorchar.c common.o

find_xor_key: 4/find_xor_key.c common.o
	$(CC) -o find_xor_key $(CFLAGS) 4/find_xor_key.c common.o

repkey_xor: 5/repkey_xor.c common.o
	$(CC) -o repkey_xor $(CFLAGS) 5/repkey_xor.c common.o

hex_repkey_xor: 5/hex_repkey_xor.c common.o
	$(CC) -o hex_repkey_xor $(CFLAGS) 5/hex_repkey_xor.c common.o

base64_repkey_xor: base64_repkey_xor.c common.o
	$(CC) -o base64_repkey_xor $(CFLAGS) base64_repkey_xor.c common.o

crack-rot-xor: 6-crack-rotating-xor/crack-rot-xor.c common.o
	$(CC) -o crack-rot-xor $(CFLAGS) common.o 6-crack-rotating-xor/crack-rot-xor.c

editdistance: util/editdistance.c common.o
	$(CC) -o editdistance $(CFLAGS) util/editdistance.c common.o

outputscores__3: outputscores__3.c common.o
	$(CC) $(CFLAGS) -o outputscores__3 outputscores__3.c common.o 

base64tohex: util/base64tohex.c common.o
	$(CC) -o base64tohex $(CFLAGS) util/base64tohex.c common.o


hextoascii: util/hextoascii.c common.o
	$(CC) -o hextoascii util/hextoascii.c common.o

b64: util/b64.c common.o
	$(CC) $(CFLAGS) -o b64 util/b64.c common.o

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c

test: all
	touch test

clean:
	rm common.o
	rm find_xor_key b64 base64tohex test editdistance xor xorchar crack-rot-xor hextoascii hex_repkey_xor base64_repkey_xor repkey_xor b64

.PHONY: clean all

