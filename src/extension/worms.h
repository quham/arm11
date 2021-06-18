#include <stdbool.h>

#ifndef WORMSCII_H
#define WORMSCII

// Game Settings
#define SHOT_DAMAGE 50

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
#define POWER_SPEED_MODIFIER 10
void playerTurn(player, player_input);
void updateCoord(coordinate, char);
bool isTankCollision(coordinate);
void movePlayer(player *player, int movement_no, int direction);
void swapPlayer(player **);

// Parabola
#define PI 3.14159
#define GRAVITY 9.8
#define INTERVAL_MULTIPLIER 0.7
void parabola(player_input, coordinate *);
double timeInterval(player_input input);
void printParabola(coordinate points[]);
bool isCollision(coordinate);
bool isTankCol(coordinate);
bool isMapCol(coordinate);
double getY(double initial_velocity, double angle, double time);
double getX(double initial_velocity, double angle, double time);
double toRadians(double angle);
bool isTermCoord(coordinate coord);
double timeOfFlight(player_input);

// Map
void printMap(void);
void initializeMap(void);
void addTank(player);
void removeTank(player);
bool inBounds(coordinate);
bool aboveMap(coordinate);

// Wormscii
#define INPUT_SIZE 4
#define MAX_HEALTH 100
#define MAX_POWER 100
#define MIN_POWER 10
#define P1_X_OFFSET 5
#define P2_X_OFFSET (MAP_WIDTH - 5)
#define P_Y_OFFSET (MAP_HEIGHT - 10)
#define POWER_SCALE 0.5
void makeMove(player *player);
player_input getPlayerShot(void);
bool boolPlayerInput(void);
bool digitInput(char input[]);
int getInt(void);
void printHealth(void);
void startAnimation(void);
void exitAnimation(void);
void getLine(char *input);
void announceWinner(int player_number);
bool haveWinner(void);

// Graphics

#define EXIT_TEXT \
  ("\n\n\n\n\n\
       @@@@@@   @@@@@@   @@@@@@  @@@@@@   @       @   @@@@@@  @       @      \n\
       @        @   ~@   @    @  @        @   @   @   @   ~   @       @      \n\
       @@@      @@@@@@   @@@@@@  @@@@@    @  @ @  @   @@@@@   @       @      \n\
       @        @    @   @  @    @   ~    @ @   @ @   @       @       @      \n\
       @        @    @   @   @@  @@@@@@   @      ~@   @@@@@@  @@@@@@  @@@@@@ \n\n\n\
                    THANK YOU FOR PLAYING, SEE YOU AGAIN SOON!\n\n\n\n\n")

#define WELCOME_TEXT \
  ("\n\n\n\n\n\
       @       @   @@@@@@   @        @@@@@@   @@@@@@   @       @   @@@@@@ \n\
       @   @   @   @        @        @        @    @   @ @   @ @   @      \n\
       @  @ @  @   @@@@@    @        @        @    @   @  @ @  @   @@@@@  \n\
       @ @   @ @   @        @   ~    @        @    @   @   @   @   @  ~   \n\
       @       @   @@@@@@   @@@@@@   @@@@@@   @@@@@@   @       @   @@@@@@ \n\
                                                                          \n\
                                @@@@@@@   @@@@@@                          \n\
                                   @      @    @      `@`                 \n\
                                   @      @    @       `  .      worm inside         \n\
                    !              @      @ ~  @           .    /          \n\
                    _/             @      @@@@@@            \\_           \n\
                   |~|        ~                             |~|           \n\
       @       @   @@@@@@   @@@@@@   @       @   @@@@@@   @@@@@@   @    @ \n\
       @   @   @   @    @   @    @   @ @   @ @   @        @        @    @ \n\
       @  @ @  @   @    @   @@@@@@   @  @ @  @    @@@@    @        @    @ \n\
       @ @   @ @   @ ~  @   @  @     @   @   @        @   @ ~      @    @ \n\
       @       @   @@@@@@   @   @@   @       @   @@@@@@   @@@@@@   @    @ \n\n\n\
                     Please expand your terminal accordingly\n\n\n\n\n")

#endif  // WORM_CONSTS
