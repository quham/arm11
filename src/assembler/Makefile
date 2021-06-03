CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -std=c99 -Werror -pedantic
PROGS   = assemble

.SUFFIXES: .c .o

.PHONY: all 

.PHONY: all clean

all: assemble

assemble: assemble.o tokenizer.o multiply.o single_data_transfer.o symbol_table.o instr_compose.o data_processing.o branch.o bit_maniplation.o
	$(CC) -o $(PROGS) assemble.o tokenizer.o multiply.o single_data_transfer.o symbol_table.o instr_compose.o data_processing.o branch.o bit_maniplation.o

assemble.o: ass_general.h arm_general.h

tokenizer.o: ass_general.h

multiply.o: ass_general.h

single_data_transfer.o: ass_general.h

symbol_table.o: ass_general.h

instr_compose.o: ass_general.h

data_processing.o: ass_general.h

branch.o: ass_general.h

bit_maniplation.o: arm_general

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
