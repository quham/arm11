#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "worms.h"

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT * MAP_WIDTH];
  // TODO IMPORTANT: FIND MAX SIZE (flight time / interval)
  coords[0] = player.curr_coord;
  parabola(input, coords);

  int interval = ceil((double)input.power / 10);  // magic number
  for (int i = 2; !isTermCoord(coords[i]); i++) {
    updateCoord(coords[i], BOMB_CHR);
    updateCoord(coords[i - 1], TRAIL_CHR);
    if (i % interval == 0) {
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

void makeMove(player *player) {
  char answer[INPUT_SIZE];
  printf("Do you want to move a tank?(yes/no): ");
  getLine(answer);
  if (!strcmp(answer, "yes")) {
    printf("Enter the direction(l/r): ");
    getLine(answer);
    for (; strcmp(answer, "l") && strcmp(answer, "r"); getLine(answer)) {
      printf("Please try again: ");
    }
    printf("Enter desired movement number: ");
    int move_no = getInt();
    int direction = !strcmp(answer, "l") ? -1 : 1;
    movePlayer(player, move_no, direction);
    printMap();
    printHealth();
  } else if (!strcmp(answer, "no")) {
    return;
  } else {
    makeMove(player);
  }
}
