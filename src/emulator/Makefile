CC      =       gcc
CFLAGS  =       -Wall
BUILD   =       data_processing

all: 	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core
data_processing: 	data_processing.o
data_processing.o: 	em_general.h instr_decompose.c

