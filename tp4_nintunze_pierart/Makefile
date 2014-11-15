.PHONY : clean fclean test all

CC = gcc
CFLAGS = -Wall -Werror -B -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all :  mcat-scd test

mcat-scd: mcat-scd.c fatal.c fatal.h
	$(CC) $(CFLAGS) -o $@ fatal.c $< -D MCAT_BUFSIZ
	chmod +x mcat.sh


test: clean
	./mcat.sh


clean :
	rm -f *.o *~

fclean : clean
	rm -f mcat-scd
