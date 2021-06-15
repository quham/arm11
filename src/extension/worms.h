#ifndef WORMSCII_H
#define WORMSCII_H

#include <stdbool.h>

/* TO BE CONFIRMED */
#define MAP_WIDTH 132
#define MAP_HEIGHT 40
#define TERM_COORD ((coordinate){-1, -1})

typedef struct coordinate {
  int x;
  int y;
} coordinate;

typedef struct player_input {
  int angle;
  int power;
} player_input;

typedef struct player {
  coordinate curr_coord;
  int health;
} player;

extern char map[MAP_HEIGHT][MAP_WIDTH];
extern player player_1, player_2;

// Player turn
void playerTurn(player, player_input);
void updateCoord(coordinate, char);
bool isTankCollision(coordinate);

// Parabola
#define PI 3.14159
#define GRAVITY 9.8
#define TIME_INTERVAL 0.1
void parabola(player_input, coordinate *);
void printParabola(coordinate points[]);

// Map
void printMap();
void initializeMap();
void addTanks(void);
bool inBounds(coordinate);
bool aboveMap(coordinate);

// Wormscii
#define INPUT_SIZE 4
#define MAX_POWER 100
#define MIN_POWER 10
player_input getPlayerInput(void);
bool digitInput(char input[]);
int getInt(void);
void startAnimation(void);
void exitAnimation(void);
void getLine(char *input);
void announceWinner(int player_number);

#endif
