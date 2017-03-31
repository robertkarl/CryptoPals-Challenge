CC=gcc
CFLAGS = -I. -Wstrict-prototypes -Wall -g -pedantic -ansi -I./libs -Werror

all: xor editdistance hextoascii crack-rot-xor find_xor_key b64 hex 7 8 cbc

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

pad_pkcs: util/pkcs.c
	$(CC) $(CFLAGS) -o pad_pkcs util/pkcs.c

cbc: cbc.c aes.o common.o
	$(CC) -pedantic -Wall -o cbc cbc.c -I./libs aes.o common.o

aes.o: libs/aes.c
	$(CC) -c -g -Wall -pedantic -Wstrict-prototypes libs/aes.c -I./libs

7: aes.o common.o
	$(CC) -pedantic -g -Wall -I./libs -o 7 7-aes/7.c aes.o common.o

8: 8-detect-aes/8.c
	$(CC) $(CFLAGS) -o 8 8-detect-aes/8.c

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c

testb64:
	./b64 < testfiles/lyrics.txt | ./b64 --decode > out.txt
	diff testfiles/lyrics.txt out.txt

testhex:
	./hex < testfiles/lyrics.txt | ./hex --decode > out.txt
	diff out.txt testfiles/lyrics.txt

testxor:
	./xor ICE < testfiles/lyrics.txt | ./hex  > out.txt
	diff out.txt testfiles/lyrics.xored.txt

test: all testb64 testhex testxor
	touch test
	rm out.txt

clean:
	rm -f common.o
	rm -f pad_pkcs test find_xor_key test editdistance xor crack-rot-xor hextoascii b64 hex 7 8 cbc
	rm -f same.lyrics.txt lyrics.base64

.PHONY: testb64 clean all

