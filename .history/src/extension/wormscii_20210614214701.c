#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "worms.h"

char map[MAP_HEIGHT][MAP_WIDTH];

int main(void) {
  startAnimation();
  initializeMap();
  player player_1 = {{5, MAP_HEIGHT - 9}, 100}; // TODO: define constants
  player player_2 = {{MAP_WIDTH - 5, MAP_HEIGHT - 9}, 100};

  player *current_player = &player_1;
  while (true) {
    player_input input = getPlayerInput();
    current_player = (current_player == &player_1) ? &player_2 : &player_1;
    playerTurn(*current_player, input);
    if (player_1.health <= 0) {
      announceWinner(2);
      break;
    }
    if (player_2.health <= 0) {
      announceWinner(1);
      break;
    }
  }
  exitAnimation();
  return EXIT_SUCCESS;
}

player_input getPlayerInput(void) {
  player_input input;

  printf("Enter the %% power: ");
  int power = getInt();
  for (; power > MAX_POWER; power = getInt()) {
    printf("Power should be below %d%%, try again: ", MAX_POWER);
  }
  input.power = power;

  printf("Enter the angle: ");
  input.angle = getInt();

  return input;
}

int getInt(void) {
  char input[INPUT_SIZE];
  for (getLine(input); !digitInput(input); getLine(input)) {
    printf("Invalid input, please try again: ");
  }
  return strtol(input, NULL, 10);
}

void getLine(char *input) {
  fflush(stdin);
  assert(fgets(input, INPUT_SIZE, stdin));
  if (input[strlen(input) - 1] == '\n') {
    input[strlen(input) - 1] = '\0';
  }
}

bool digitInput(char input[]) {
  for (int i = 0; i < strlen(input); i++) {
    if (!isdigit(input[i])) {
      return false;
    }
  }
  return input[0] != '0';  // input cant have leading 0
}

void startAnimation(void) {}

void exitAnimation(void) {}

void announceWinner(int player_number) {
  printf("\nPlayer %d Wins!\n", player_number);
}
