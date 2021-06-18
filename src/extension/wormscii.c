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
  player_input input;
  player_1 = (player){{P1_X_OFFSET, P_Y_OFFSET}, MAX_HEALTH, 1};
  player_2 = (player){{P2_X_OFFSET, P_Y_OFFSET}, MAX_HEALTH, 2};
  initializeMap();
  printMap();
  player *current_player = &player_1;

  while (!haveWinner()) {
    printHealth();
    printf("Player %d's Turn\n", current_player->player_no);
    makeMove(current_player);
    input = getPlayerInput();
    input.angle = current_player->player_no == 1 ? input.angle : 180 - input.angle;
    playerTurn(*current_player, input);
    swapPlayer(&current_player);
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
  input.power = power / POWER_DIVISION;

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
  assert(fgets(input, INPUT_SIZE, stdin));

  bool is_stdin_clear = false;
  if (input[strlen(input) - 1] == '\n') {
    input[strlen(input) - 1] = '\0';
    is_stdin_clear = true;
  }

  if (!is_stdin_clear) {
    char ch = getchar();
    while (ch != '\n') {
      ch = getchar();
    }
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

// TODO: refactor into constant
void startAnimation(void) {
  system("clear");
  printf("%s", WELCOME_TEXT);

  char input[INPUT_SIZE];

  for (getLine(input); strcmp(input, "yes") != 0; getLine(input)) {
    if (strncmp(input, "no", INPUT_SIZE) == 0) {
      printf(EXIT_TEXT);
      exit(EXIT_SUCCESS);
    }
    printf("Invalid input, please try again: ");
  }
  system("clear");
}

void exitAnimation(void) {
  printf(EXIT_TEXT);
}

bool haveWinner(void) {
  if (player_1.health <= 0) {
    announceWinner(player_2.player_no);
    return true;
  }
  if (player_2.health <= 0) {
    announceWinner(player_1.player_no);
    return true;
  }
  return false;
}

void announceWinner(int player_number) {
  printf("\nPlayer %d Wins!\n", player_number);
}
