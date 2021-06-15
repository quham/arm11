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
  for (int i = 1; coords[i + 1].x != TERM_COORD.x; i++) {
    if (i % 1 == 0) {  // TODO: change '1' to something based on time
      updateCoord(coords[i], BOMB_CHR);
      printMap();
      nanosleep((struct timespec[]){{0, 10000000}}, NULL);
    }
  }
  nanosleep((struct timespec[]){{0, 500000000}}, NULL);
  for (int i = 1; coords[i].x != -1; i++) {
    updateCoord(coords[i],EMPTY_CHR);
  }
}

void updateCoord(coordinate coord, char ch) {
  if (!aboveMap(coord)) {
    map[coord.y][coord.x] = ch;
  }
}
