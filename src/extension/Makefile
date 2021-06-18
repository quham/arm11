CC     = gcc 
CFLAGS = -Wall -g -D_POSIX_SOURCE_C_SOURCE=199309L -DEFAULT_SOURCE -std=gnu99 -Werror -pedantic
LIBS   = -lm

WORMSCII_OBJ := $(patsubst %.c, %.o, $(shell find *.c))

.SUFFIXES: .c .o

.PHONY: all clean

all: wormscii

wormscii: $(WORMSCII_OBJ)
				$(CC) $(CFLAGS)	$(WORMSCII_OBJ) -o wormscii $(LIBS)

wormscii.o: worms.h

clean:
	rm -f $(wildcard *.o)
	rm -f wormscii
