#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '
#define TRAIL_CHR '.'

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT * MAP_WIDTH];
  coords[0] = player.curr_coord;
  parabola(input, coords);
  // TODO: trailing chars
  updateCoord(coords[1], BOMB_CHR);
  double scale = 1 / (input.power * 0.5);
  int interval = input.power / 10;
  for (int i = 2; coords[i].x != TERM_COORD.x; i++) {
    if (i % interval == 0) {  // TODO: change '1' to something based on time
      updateCoord(coords[i], BOMB_CHR);
      updateCoord(coords[i-interval], TRAIL_CHR);
      printMap();
      nanosleep((struct timespec[]){{0,(int) 1000000000.0 * scale}}, NULL);
    }
  }
  nanosleep((struct timespec[]){{0, 1500000000}}, NULL);
  for (int i = 1; coords[i].x != -1; i++) {
    updateCoord(coords[i],EMPTY_CHR);
  }
}

void updateCoord(coordinate coord, char ch) {
  if (!aboveMap(coord)) {
    map[coord.y][coord.x] = ch;
  }
}
