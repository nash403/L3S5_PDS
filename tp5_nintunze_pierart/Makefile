.PHONY : clean fclean test all

CC = gcc
CFLAGS = -Wall -Werror -B -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all : ff race test

ff: ff.c forkfork.o forkfork.h
	$(CC) $(CFLAGS) -o $@ forkfork.o $<

forkfork.o : forkfork.c
	$(CC) $(CFLAGS) -c $<

race: race.c
	$(CC) $(CFLAGS) -o $@ $<

test: clean
	bash sessionTest.sh


clean :
	rm -f *.o *~

fclean : clean
	rm -f ff race
