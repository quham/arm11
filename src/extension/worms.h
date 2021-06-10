#ifndef WORMSCII_H
#define WORMSCII_H

/* TO BE CONFIRMED */
#define MAP_WIDTH 64
#define MAP_HEIGHT 128

typedef struct coordinate {
  double x;
  double y;
} coordinate;

typedef struct player_input {
  double angle;
  double power;  // inital velocity ?
} player_input;

coordinate *parabola(player_input input);

#endif