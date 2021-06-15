#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "worms.h"

char map[MAP_HEIGHT][MAP_WIDTH];
player player_1, player_2;

int main(void) {
  startAnimation();
  player_1 = (player){{5, MAP_HEIGHT - 10}, MAX_HEALTH, 1};  // TODO: define constants
  player_2 = (player){{MAP_WIDTH - 5, MAP_HEIGHT - 10}, MAX_HEALTH, 2};
  initializeMap();
  printMap();
  player_input input;
  player *current_player = &player_1;

  while (true) {
    printHealth();
    printf("Player %d's Turn\n", current_player->player_no);
    input = getPlayerInput();
    input.angle = current_player->player_no == 1 ? input.angle : 180 - input.angle;
    playerTurn(*current_player, input);
    if (haveWinner()) {
        break;
    }
    current_player = swapPlayer(current_player);
  }

  exitAnimation();
  return EXIT_SUCCESS;
}

void printHealth(void) {
  printf("Player 1, current health: %d\n", player_1.health);
  printf("Player 2, current health: %d\n", player_2.health);
}

player_input getPlayerInput(void) {
  player_input input;

  printf("Enter the %% power: ");
  int power = getInt();
  for (; power > MAX_POWER || power < MIN_POWER; power = getInt()) {
    printf("Power should be in range %d..%d%%, try again: ", MIN_POWER, MAX_POWER);
  }
  input.power = power / 2;  // temporary division

  printf("Enter the angle: ");
  input.angle = getInt() % 360;

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

bool haveWinner(void) {
    if (player_1.health <= 0) {
        announceWinner(2);
        return true;
    }
    if (player_2.health <= 0) {
        announceWinner(1);
        return true;
    }
    return false;
}

player *swapPlayer(player *current_player) {
    if (current_player->player_no == 1) {
        return &player_2;
    } else {
        return &player_1;
    }
}

void announceWinner(int player_number) {
  printf("\nPlayer %d Wins!\n", player_number);
}
