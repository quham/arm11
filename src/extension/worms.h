#ifndef WORMSCII_H
#define WORMSCII_H

#include <stdbool.h>

/* TO BE CONFIRMED */
#define MAP_WIDTH 132
#define MAP_HEIGHT 40

typedef struct coordinate {
  int x;
  int y;
} coordinate;

typedef struct player_input {
  double angle;
  double power;  // inital velocity ?
} player_input;

extern char map[MAP_HEIGHT][MAP_WIDTH];

// parabola.c
void parabola(player_input input, coordinate* coords);
void printParabola(coordinate points[]);

// map.c
void printMap();
void initializeMap();

// Wormscii.c
player_input getPlayerInput(void);
void printInput(player_input input);
bool checkInput(char input[]);
int getInt(void);

#endif
