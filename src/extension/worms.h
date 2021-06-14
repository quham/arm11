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
  int angle;
  int power;
} player_input;

typedef struct player {
  coordinate curr_position;
  int health;
} player;

extern char map[MAP_HEIGHT][MAP_WIDTH];

// Player turn
void playerTurn(player, player_input);

// Parabola
void parabola(player_input, coordinate*);
void printParabola(coordinate points[]);

// Map
void printMap();
void initializeMap();

// Wormscii
#define INPUT_SIZE 4
#define MAX_POWER 100
player_input getPlayerInput(void);
bool digitInput(char input[]);
int getInt(void);
void startAnimation(void);
void exitAnimation(void);
void getLine(char *input);
void announceWinner(int player_number);

#endif
