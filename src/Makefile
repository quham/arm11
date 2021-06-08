CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic

ASSEMBLER_OBJ := $(patsubst %.c, %.o, $(shell find assembler -type f -name '*.c')) bit_manipulation.o
EMULATOR_OBJ := $(patsubst %.c, %.o, $(shell find emulator -type f -name '*.c')) bit_manipulation.o

.SUFFIXES: .c .o

.PHONY: all clean

all: assembler/assemble emulator/emulate

assembler/assemble: assembler/assemble.o $(ASSEMBLER_OBJ) 

emulator/emulate: emulator/emulate.o $(EMULATOR_OBJ)

assemble.o: assembler/ass_general.h

emulate.o: emulator/em_general.h

clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard assembler/*.o)
	rm -f $(wildcard emulator/*.o)
	rm -f assembler/assemble
	rm -f emulator/emulate
