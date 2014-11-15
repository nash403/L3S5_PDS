.PHONY : clean fclean test all

CC = gcc
CFLAGS = -Wall -Werror -B -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all : tailSimpliste tailCirculaire tailEfficace test

tailSimpliste: tailSimpliste.c fatal.c fatal.h
	$(CC) $(CFLAGS) -o mtail1 fatal.c $<

tailCirculaire: tailBufferCirculaire.c fatal.c fatal.h
	$(CC) $(CFLAGS) -o mtail2 fatal.c $<

tailEfficace: tailEfficace.c fatal.c fatal.h
	$(CC) $(CFLAGS) -o mtail3 fatal.c $<


test: clean
	bash sessionTest.sh


clean :
	rm -f *.o *~

fclean : clean
	rm -f mtail1 mtail2 mtail3
