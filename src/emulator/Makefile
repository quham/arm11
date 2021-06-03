CC = gcc 
CFLAGS = -Wall -g -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
PROGS = emulate

.PHONY: all

all: emulate

emulate: pipeline.o emulate.o single_data_transfer.o multiply.o data_processing.o check_condition.o branch.o instr_decompose.o 
	$(CC) -o $(PROGS) pipeline.o emulate.o single_data_transfer.o multiply.o data_processing.o check_condition.o branch.o instr_decompose.o 

emulate.o: em_general.h

pipeline.o: em_general.h

clean:
	rm -f *.o emulate $(PROGS) *~
 

