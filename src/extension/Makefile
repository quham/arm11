CC     = gcc 
CFLAGS = -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic
LIBS   = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: wormscii

<<<<<<< HEAD
wormscii: wormscii.o map.o collision_detector.o parabola.o player_turn.o update_coord.o
	$(CC) $(CFLAGS)	wormscii.o parabola.o map.o -o wormscii $(LIBS)
=======
wormscii: wormscii.o map.o parabola.o player_turn.o
	$(CC) $(CFLAGS)	wormscii.o parabola.o -o wormscii $(LIBS)
>>>>>>> c77c9fbceff97bb92445cdbd83ae094b8bc8545c

wormscii.o: worms.h

parabola.o: worms.h

map.o: worms.h wormscii.o

clean:
	rm -f $(wildcard *.o)
	rm -f wormscii
