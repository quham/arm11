#include <stdio.h>

#include "worms.h"

#define BOTTOM_GROUND 0.8
#define MIDDLE_GROUND 0.6
#define UPPER_SKY 0.45

#define UPPER_HILL_START 0.50
#define UPPER_HILL_END 0.68

#define BOTTOM_HILL_START 0.37
#define BOTTOM_HILL_END 0.68

void initializeMap() {
  // initializes upper part
  for (int i = 0; i < MAP_HEIGHT * UPPER_SKY; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      map[i][j] = ' ';
    }
  }
  // initializes upper half of the hill
  for (int i = MAP_HEIGHT * UPPER_SKY; i < MAP_HEIGHT * MIDDLE_GROUND; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (MAP_WIDTH * UPPER_HILL_START < j && j < MAP_WIDTH * UPPER_HILL_END) {
        map[i][j] = '#';
      } else {
        map[i][j] = ' ';
      }
    }
  }
  // initializes bottom half of the hill
  for (int i = MAP_HEIGHT * MIDDLE_GROUND; i < MAP_HEIGHT * BOTTOM_GROUND; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (MAP_WIDTH * BOTTOM_HILL_START < j && j < MAP_WIDTH * BOTTOM_HILL_END) {
        map[i][j] = '#';
      } else {
        map[i][j] = ' ';
      }
    }
  }
  // initializes bottom part
  for (int i = MAP_HEIGHT * BOTTOM_GROUND; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      map[i][j] = '#';
    }
  }
}

// TODO: movement seperate into add each tank and make remove tank
void addTanks(void) {
  int x = player_1.curr_position.x;
  int y = player_1.curr_position.y;
  map[x][y] = '/';
  map[x - 1][y] = '-';
  map[x][y + 1] = '|';
  map[x - 1][y + 1] = '1';
  map[x - 2][y + 1] = '|';
  x = player_2.curr_position.x;
  y = player_2.curr_position.y;
  map[x][y] = '\\';
  map[x + 1][y] = '-';
  map[x][y + 1] = '|';
  map[x + 1][y + 1] = '2';
  map[x + 2][y + 1] = '|';
}

void printMap() {
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
