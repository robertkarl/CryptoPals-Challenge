CC=gcc
CFLAGS = -I. -Wstrict-prototypes -Wall -g -pedantic -ansi
DEPS = common.h

OBJS = common.o hextobase64.o

hex2base64: $(OBJS)
	$(CC) -o bin/hex2base64 $(OBJS)

xorbuffers: xor.c common.o
	$(CC) -o bin/xorbuffers $(CFLAGS) xor.c common.o

hextobase64.o: hextobase64.c common.h
	$(CC) -c $(CFLAGS) hextobase64.c

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c
clean:
	rm bin/*
	rm -f *.o
	rm -f hex2base64
