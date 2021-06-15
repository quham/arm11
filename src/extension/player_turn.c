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
      system("clear");  // not a good way of clearing screen
      printMap();
      nanosleep((struct timespec[]){{0, 10000000}}, NULL);
    }
  }
  nanosleep((struct timespec[]){{0, 500000000}}, NULL);
}

void updateCoord(coordinate coord, char ch) {
  if (!aboveMap(coord)) {
    map[coord.y][coord.x] = ch;
  }
}

// TODO: fix
bool isTankCollision(coordinate coord) {
  // int x1 = player_1.curr_coord.x;
  // int x2 = player_2.curr_coord.x;
  // char ch = map[coord.y][coord.x];
  // if (ch != '#' && ch != ' ') {
  //   if (abs(coord.x - x1) < abs(coord.x - x2)) {
  //     player_1.health -= 10;
  //   } else {
  //     player_2.health -= 10;
  //   }
  //   return true;
  // }
  return false;
}
