#ifndef WORMSCII_H
#define WORMSCII_H

#include <stdbool.h>

/* TO BE CONFIRMED */
#define MAP_WIDTH 132
#define MAP_HEIGHT 40


typedef struct coordinate {
  double x;
  double y;
} coordinate;

typedef struct player_input {
  double angle;
  double power;  // inital velocity ?
} player_input;

coordinate *parabola(player_input input);
// map.c
void printMap(char map[MAP_HEIGHT][MAP_WIDTH]);
void initializeMap(char map[MAP_HEIGHT][MAP_WIDTH]);

// Wormscii.c
player_input getPlayerInput(void);
void printInput(player_input input);
bool checkInput(char input[]);
int getInt(void);

#endif
