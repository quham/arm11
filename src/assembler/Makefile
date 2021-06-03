CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -std=c99 -Werror -pedantic
PROGS   = assemble

.SUFFIXES: .c .o

.PHONY: all 

.PHONY: all clean

all: assemble

assemble: assemble.o tokenizer.o multiply.o
	$(CC) -o $(PROGS) assemble.o tokenizer.o multiply.o

assemble.o: ass_general.h tokenizer.h

tokenizer.o: tokenizer.h ass_general.h

multiply.o: tokenizer.h ass_general.h



clean:
	rm -f $(wildcard *.o)
	rm -f assemble
