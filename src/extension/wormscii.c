#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "worms.h"

#define MAX_POWER 100
#define INPUT_SIZE 10  // 10 should be enough for small integers

char map[MAP_HEIGHT][MAP_WIDTH];

int main(void) {
    printf("                                    \n");
    printf("      ~^~@  WELCOME TO WORMSCII  @~^~\n");
    printf("\n");
    printf(" *~       HELP THE WORLD RECOVER  ~*     \n");
    printf("   ~*  EXTERMINATE MISBEHAVING WORMS  *~ \n\n");
    //INTRODUCTION / GAME RULES ??
    system("clear");

    
    initializeMap();

    player_input input = {60, 30};
   
    //printf("%f\n", tan(3.14159));
    coordinate coords[MAP_HEIGHT * MAP_WIDTH] = {0};
    
    coords[0] = (coordinate) {5, (MAP_HEIGHT - 9)};
    parabola(input, coords);

    printParabola(coords);

    // ENTER GAME LOOP
    //while(1)
    /*player_input input = {55, 40};
    coordinate * curve = parabola(input);
    for (int i = 0; i < 128 * 2; i ++) {
        printf("(%d , %d)\n", (int) (curve->x), (int) (curve->y));
        curve++;
        if (curve->x == 0 && curve->y == 0) {
            break;
        }
    }*/
    //player_input input = getPlayerInput();
//    printInput(input);

    return 0;
}

void printInput(player_input input) {
  printf("Power is %lf, angle is %lf \n", input.power, input.angle);
}

player_input getPlayerInput(void) {
  player_input input;
  int angle, power;

  printf("Enter the power: ");
  power = getInt();

  printf("Enter the angle: ");
  angle = getInt() % 360;

  while (power > MAX_POWER) {
    printf("Power should be in a range 0..%d, try again: ", MAX_POWER);
    power = getInt();
  }
  input.power = (double)power;
  input.angle = (double)angle;
  return input;
}

bool checkInput(char input[]) {
  for (int i = 0; i < strlen(input); i++) {
    if (isdigit(input[i]) == 0) {
      return false;
    }
  }
  return true;
}

int getInt(void) {
  char input[10];
  scanf("%s", input);
  while (!checkInput(input)) {
    ;
    printf("Invalid input, please try again: ");
    scanf("%s", input);
  }
  return strtol(input, NULL, 10);
}
