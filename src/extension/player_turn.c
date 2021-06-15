#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void movePlayer(player *player, int movement_no, int direction) {
    int move_no = 0;
    int move_offset = 0;
    if (player->player_no == 1) {
        if(direction == -1) {
            move_offset = -2;
        }
    } else {
        if (direction == 1) {
            move_offset = 2;
        }
    }

    // ensures safety of the move
    // just checks for one point, so the pointy edge wont work
    coordinate p1 = {player->curr_coord.x + move_offset, player->curr_coord.y};
    while (abs(move_no) < movement_no) {
        p1.x += direction;
        if (!inBounds(p1) || map[p1.y][p1.x] != ' ') {
            break;
        }
        move_no += direction;
    }
    removeTank(*player);
    player->curr_coord.x += move_no;
    addTank(*player);
}

