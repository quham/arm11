#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

#define BOTTOM_GROUND 0.8
#define MIDDLE_GROUND 0.6
#define UPPER_SKY 0.45

#define UPPER_HILL_START 0.50
#define UPPER_HILL_END 0.68

#define BOTTOM_HILL_START 0.37
#define BOTTOM_HILL_END 0.68

void initializeMap(void) {
  // initializes upper part
  for (int i = 0; i < MAP_HEIGHT * UPPER_SKY; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      map[i][j] = EMPTY_CHR;
    }
  }
  // initializes upper half of the hill
  for (int i = MAP_HEIGHT * UPPER_SKY; i < MAP_HEIGHT * MIDDLE_GROUND; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (MAP_WIDTH * UPPER_HILL_START < j && j < MAP_WIDTH * UPPER_HILL_END) {
        map[i][j] = MAP_CHR;
      } else {
        map[i][j] = EMPTY_CHR;
      }
    }
  }
  // initializes bottom half of the hill
  for (int i = MAP_HEIGHT * MIDDLE_GROUND; i < MAP_HEIGHT * BOTTOM_GROUND; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (MAP_WIDTH * BOTTOM_HILL_START < j && j < MAP_WIDTH * BOTTOM_HILL_END) {
        map[i][j] = MAP_CHR;
      } else {
        map[i][j] = EMPTY_CHR;
      }
    }
  }
  // initializes bottom part
  for (int i = MAP_HEIGHT * BOTTOM_GROUND; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      map[i][j] = MAP_CHR;
    }
  }
  addTank(player_1);
  addTank(player_2);
}

bool inBounds(coordinate coord) {
  return coord.x >= 0 && coord.x < MAP_WIDTH;
}

bool aboveMap(coordinate coord) {
  return coord.y < 0;
}

void printMap(void) {
  system("clear");  // not a good way of clearing screen
  printf(" ");
  for (int i = 0; i < MAP_WIDTH; i++) {
    printf("-");
  }

  printf("\n");
  for (int i = 0; i < MAP_HEIGHT; i++) {
    printf("|");
    for (int j = 0; j < MAP_WIDTH; j++) {
      printf("%c", map[i][j]);
    }
    printf("|\n");
  }
  printf(" ");
  for (int i = 0; i < MAP_WIDTH; i++) {
    printf("-");
  }
  printf("\n");
}

void addTank(player player) {
  int x = player.curr_coord.x;
  int y = player.curr_coord.y;
  int player_offset = player.player_no == 1 ? 1 : -1;
  char turret = player.player_no == 1 ? '/' : '\\';
  map[y][x] = turret;
  map[y][x - player_offset] = '_';
  map[y + 1][x] = '|';
  map[y + 1][x - player_offset] = '0' + player.player_no;
  map[y + 1][x - 2 * player_offset] = '|';
}

void removeTank(player player) {
  int x = player.curr_coord.x;
  int y = player.curr_coord.y;
  int player_offset = player.player_no == 1 ? 1 : -1;
  map[y][x] = ' ';
  map[y][x - player_offset] = ' ';
  map[y + 1][x] = ' ';
  map[y + 1][x - player_offset] = ' ';
  map[y + 1][x - 2 * player_offset] = ' ';
}
