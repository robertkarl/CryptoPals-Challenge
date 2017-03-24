CC=gcc
CFLAGS = -I. -Wall -g -pedantic -ansi
DEPS = common.h

OBJS = common.o hextobase64.o

hex2base64: $(OBJS)
	$(CC) -o hex2base64 $(OBJS)

hextobase64.o: hextobase64.c common.h
	$(CC) -c $(CFLAGS) hextobase64.c

common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c
clean:
	rm -f *.o
	rm -f hex2base64
