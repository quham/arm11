#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "worms.h"

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT * MAP_WIDTH];
  coords[0] = player.curr_coord;
  parabola(input, coords);

  updateCoord(coords[1], BOMB_CHR);
  // double scale = 1 / (input.power * 0.75);
  int interval = 1;  // TODO: change '1' to something based on time
  for (int i = 2; coords[i].x != TERM_COORD.x; i++) {
    if (i % interval == 0) {
      updateCoord(coords[i], BOMB_CHR);
      updateCoord(coords[i - interval], TRAIL_CHR);
      printMap();
      nanosleep((struct timespec[]){{0, 10000000}}, NULL);
    }
  }
  nanosleep((struct timespec[]){{0, 500000000}}, NULL);
  for (int i = 1; coords[i].x != -1; i++) {
    updateCoord(coords[i], EMPTY_CHR);
  }
  printMap();
}

void updateCoord(coordinate coord, char ch) {
  if (!aboveMap(coord)) {
    map[coord.y][coord.x] = ch;
  }
}
