#ifndef WORMSCII_H
#define WORMSCII_H

#include <stdbool.h>

// Game Settings
#define SHOT_DAMAGE 20

/* TO BE CONFIRMED */
#define MAP_WIDTH 132
#define MAP_HEIGHT 40
#define TERM_COORD ((coordinate){-1, -1})

// Characters
#define BOMB_CHR '@'
#define EMPTY_CHR ' '
#define TRAIL_CHR '.'
#define MAP_CHR '#'

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
  int player_no;
} player;

extern char map[MAP_HEIGHT][MAP_WIDTH];
extern player player_1, player_2;

// Player turn
void playerTurn(player, player_input);
void updateCoord(coordinate, char);
bool isTankCollision(coordinate);
void movePlayer(player *player, int movement_no, int direction);

// Parabola
#define PI 3.14159
#define GRAVITY 9.8
#define TIME_INTERVAL 0.1
void parabola(player_input, coordinate *);
void printParabola(coordinate points[]);
bool isCollision(coordinate);
bool isTankCol(coordinate);
bool isMapCol(coordinate);
double getY(double initial_velocity, double angle, double time);
double getX(double initial_velocity, double angle, double time);
double toRadians(player_input *);

// Map
void printMap();
void initializeMap();
void addTank(player);
void removeTank(player);
bool inBounds(coordinate);
bool aboveMap(coordinate);

// Wormscii
#define INPUT_SIZE 4
#define MAX_HEALTH 100
#define MAX_POWER 100
#define MIN_POWER 10
player_input getPlayerInput(void);
bool digitInput(char input[]);
int getInt(void);
void printHealth(void);
void startAnimation(void);
void exitAnimation(void);
void getLine(char *input);
void announceWinner(int player_number);
bool haveWinner(void);
//player *swapPlayer(player *current_player);
void swapPlayer(player **current_player);
#endif
