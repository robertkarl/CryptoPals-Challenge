CC=gcc
CFLAGS = -I. -Wstrict-prototypes -Wall -g -pedantic -ansi
DEPS = common.h

OBJS = common.o hextobase64.o

hex2base64: $(OBJS)
	$(CC) -o bin/hex2base64 $(OBJS)

xor: xor.c common.o
	$(CC) -o bin/xor $(CFLAGS) xor.c common.o

4: 4.c common.o
	$(CC) -o bin/4 $(CFLAGS) 4.c common.o

5: 5/repkey_xor.c common.o
	$(CC) -o bin/5 $(CFLAGS) 5/repkey_xor.c common.o

guesskey: 6/6.c common.o
	$(CC) -o bin/6 $(CFLAGS) 6/6.c common.o

editdistance: 6/editdistance.c common.o
	$(CC) -o bin/editdistance $(CFLAGS) 6/editdistance.c common.o

repkey_xor: repkey_xor.c common.o
	$(CC) -o bin/repkey_xor $(CFLAGS) repkey_xor.c common.o

outputscores__3: outputscores__3.c common.o
	$(CC) $(CFLAGS) -o bin/outputscores__3 outputscores__3.c common.o 

base64tohex: util/base64tohex.c common.h common.o
	$(CC) -o bin/base64tohex $(CFLAGS) util/base64tohex.c common.o

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c
clean:
	rm -f bin/*
	rm -f *.o
	rm -f hex2base64
