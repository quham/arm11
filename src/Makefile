CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic

ASSEMBLER_OBJ := $(patsubst %.c, %.o, $(shell find assembler -type f -name '*.c')) bit_manipulation.o
EMULATOR_OBJ := $(patsubst %.c, %.o, $(shell find emulator -type f -name '*.c')) bit_manipulation.o

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o $(ASSEMBLER_OBJ) 

emulate: emulate.o $(EMULATOR_OBJ)

assemble.o: assembler/ass_general.h arm_general.h

emulate.o: emulator/em_general.h arm_general.h

clean:
	rm -f $(wildcard *.o)
	rm -f assembler/$(wildcard *)
	rm -f assemble
	rm -f emulate
