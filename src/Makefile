CC      = gcc
CFLAGS  = -Icommon -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic

ASSEMBLER_OBJ := $(patsubst %.c, %.o, $(shell find assembler -type f -name '*.c')) common/data_manipulation.o
EMULATOR_OBJ := $(patsubst %.c, %.o, $(shell find emulator -type f -name '*.c')) common/data_manipulation.o

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: $(ASSEMBLER_OBJ)
				$(CC) $(CFLAGS) $(ASSEMBLER_OBJ) -o assemble

emulate: $(EMULATOR_OBJ)
				$(CC) $(CFLAGS) $(EMULATOR_OBJ) -o emulate

assembler/assemble.o: assembler/ass_general.h common/arm_general.h

emulator/emulate.o: emulator/em_general.h common/arm_general.h

clean:
	rm -f $(wildcard assembler/*.o)
	rm -f $(wildcard emulator/*.o)
	rm -f $(wildcard common/*.o)
	rm -f assemble
	rm -f emulate