.PHONY : clean

CC = gcc
CFLAGS = -Wall -Werror -B -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all : prlimit maccess maccess+

prlimit : prlimit.c
	$(CC) $(CFLAGS) -o $@ $<

maccess: maccess.c fatal.c fatal.h
	$(CC) $(CFLAGS) -o $@ fatal.c $<

maccess+ : maccess+.c
	$(CC) $(CFLAGS) -o $@ $<

tests:
	cat sessionTest.txt 


clean :
	rm -f *.o *~ maccess prlimit maccess+
