CC     = gcc 
CFLAGS = -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic
LIBS   = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: wormscii

wormscii: wormscii.o map.o parabola.o player_turn.o
	$(CC) $(CFLAGS)	wormscii.o parabola.o -o wormscii $(LIBS)

wormscii.o: worms.h

parabola.o: worms.h

clean:
	rm -f $(wildcard *.o)
	rm -f wormscii
