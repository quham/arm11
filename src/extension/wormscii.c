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
    input = getPlayerShot();
    input.angle = current_player->player_no == 1 ? input.angle : 180 - input.angle;
    playerTurn(*current_player, input);
    swapPlayer(&current_player);
  }

  exitAnimation();
  return EXIT_SUCCESS;
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

void printHealth(void) {
  printf("Player %d, current health: %d\n", player_1.player_no, player_1.health);
  printf("Player %d, current health: %d\n", player_2.player_no, player_2.health);
}

void makeMove(player *player) {
  printf("Move tank");
  if (boolPlayerInput()) {
    printf("Enter the direction(l/r): ");
    char answer[INPUT_SIZE];
    getLine(answer);
    for (; strncmp(answer, "l", 1) && strncmp(answer, "r", 1); getLine(answer)) {
      printf("Please try again: ");
    }
    printf("Enter desired movement number: ");
    int move_no = getInt();
    int direction = !strncmp(answer, "l", 1) ? -1 : 1;
    movePlayer(player, move_no, direction);
    printMap();
    printHealth();
  }
}

bool boolPlayerInput(void) {
  char input[INPUT_SIZE];
  printf(" (yes/no)? ");
  for (getLine(input); strncmp(input, "yes", 3) && strncmp(input, "no", 2); getLine(input)) {
    printf("Invalid, please enter yes/no: ");
  }
  return strncmp(input, "no", 2);
}

player_input getPlayerShot(void) {
  player_input input;

  printf("Enter the %% power: ");
  int power = getInt();
  for (; power > MAX_POWER || power < MIN_POWER; power = getInt()) {
    printf("Power should be in range %d..%d%%, try again: ", MIN_POWER, MAX_POWER);
  }
  input.power = power * POWER_SCALE;

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

void startAnimation(void) {
  system("clear");
  printf(WELCOME_TEXT);
  printf("Do you want to start a game");
  if (!boolPlayerInput()) {
    exitAnimation();
    exit(EXIT_SUCCESS);
  }
  system("clear");
}

void exitAnimation(void) {
  printf(EXIT_TEXT);
}

void announceWinner(int player_number) {
  printf("\nPlayer %d Wins!\n", player_number);
}
