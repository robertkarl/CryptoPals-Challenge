CC=gcc
CFLAGS = -I. -Wstrict-prototypes -Wall -g -pedantic -ansi
DEPS = common.h

all: xor editdistance hextoascii crack-rot-xor find_xor_key b64

find_xor_key: 4/find_xor_key.c common.o
	$(CC) -o find_xor_key $(CFLAGS) 4/find_xor_key.c common.o

xor: util/xor.c common.o
	$(CC) -o xor $(CFLAGS) util/xor.c common.o

crack-rot-xor: 6-crack-rotating-xor/crack-rot-xor.c common.o
	$(CC) -o crack-rot-xor $(CFLAGS) common.o 6-crack-rotating-xor/crack-rot-xor.c

editdistance: util/editdistance.c common.o
	$(CC) -o editdistance $(CFLAGS) util/editdistance.c common.o

outputscores__3: outputscores__3.c common.o
	$(CC) $(CFLAGS) -o outputscores__3 outputscores__3.c common.o 

hextoascii: util/hextoascii.c common.o
	$(CC) -I. -o hextoascii util/hextoascii.c common.o

b64: util/b64.c common.o
	$(CC) $(CFLAGS) -o b64 util/b64.c common.o

hex: util/hex.c common.o
	$(CC) $(CFLAGS) -o hex util/hex.c common.o

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c

test: all
	touch test

clean:
	rm -f common.o
	rm -f test find_xor_key b64 test editdistance xor crack-rot-xor hextoascii b64

.PHONY: clean all

