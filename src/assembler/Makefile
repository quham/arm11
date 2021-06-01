CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -std=c99 -Werror -pedantic
PROGS   = assemble

.SUFFIXES: .c .o

.PHONY: all 

.PHONY: all clean

all: assemble

assemble: assemble.o tokenizer.o
	$(CC) -o $(PROGS) assemble.o tokenizer.o

assemble.o: ass_general.h tokenizer.h

tokenizer.o: tokenizer.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
