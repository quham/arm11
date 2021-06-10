#ifndef WORMSCII_H
#define WORMSCII_H


/* TO BE CONFIRMED */
#define MAP_WIDTH 64  
#define MAP_HEIGHT 128


typedef struct coordinate {
	int x;
	int y;
} coordinate;

typedef struct player_input {
	int angle;
	int power; //inital velocity ?
} player_input;

coordinate *parabola(player_input input);

#endif