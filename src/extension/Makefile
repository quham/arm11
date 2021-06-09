CC     = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -DEFAULT_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: wormscii

wormscii: wormscii.o map.o collision_detector.o parabola.o player_turn.o update_coord.o  

wormscii.o: worms.h

clean:
	rm -f $(wildcard *.o)
	rm -f wormscii