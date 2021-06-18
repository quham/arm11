#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "worms.h"

void playerTurn(player player, player_input input) {
  int coord_size = ceil(timeOfFlight(input) / timeInterval(input)) + 3;
  // 2 for term coord and initial coord
  coordinate coords[coord_size];
  coords[0] = player.curr_coord;
  parabola(input, coords);  // initialise coords

  if (isTermCoord(coords[1])) {
    return;
  }

  int frame_speed = ceil((double)input.power / POWER_SPEED_MODIFIER);
  for (int i = 2; !isTermCoord(coords[i]); i++) {
    updateCoord(coords[i], BOMB_CHR);
    updateCoord(coords[i - 1], TRAIL_CHR);
    if (i % frame_speed == 0) {
      printMap();
      nanosleep((struct timespec[]){{0, 10000000}}, NULL);
    }
  }
  printMap();
  nanosleep((struct timespec[]){{0, 500000000}}, NULL);

  // clear shot from map
  for (int i = 1; !isTermCoord(coords[i]); i++) {
    updateCoord(coords[i], EMPTY_CHR);
  }
  printMap();
}

bool isTermCoord(coordinate coord) {
  return coord.x == TERM_COORD.x && coord.y == TERM_COORD.y;
}

void updateCoord(coordinate coord, char ch) {
  if (!aboveMap(coord)) {
    map[coord.y][coord.x] = ch;
  }
}

void movePlayer(player *player, int movement_no, int direction) {
  int move_no = 0;
  int move_offset = 0;

  // offset movement since curr_coord isn't centred
  if (player->player_no == 1) {
    if (direction == -1) {
      move_offset = -2;
    }
  } else {
    if (direction == 1) {
      move_offset = 2;
    }
  }

  // ensures safety of the move
  // check on the bottom point of the tank
  coordinate p1 = {player->curr_coord.x + move_offset, player->curr_coord.y + 1};
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

void swapPlayer(player **current_player) {
  if ((*current_player)->player_no == 1) {
    *current_player = &player_2;
  } else {
    *current_player = &player_1;
  }
}
