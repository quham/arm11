#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"
#define PI  3.14159
#define GRAVITY 9.8

double getY(double x, double angle, double u) {
  return ((x * tan(angle)) - ((GRAVITY * pow(x, 2) * (1 + pow(tan(angle), 2)) / (2 * pow(u, 2)))));
}

player_input toRadians(player_input input) {
  input.angle = (input.angle * PI) / 180;
  return input;
}

coordinate *parabola(player_input input) {
  input = toRadians(input);

  coordinate *coords = malloc(sizeof(coordinate) * 128 * 2); //TODO: maxsize 
  coordinate position = {0, 0};
  bool is_moving = false;
  while (position.y > 0 || !is_moving) {
    position.x++; //TODO: change to use time! 
    position.y = getY(position.x, input.angle, input.power);

    coords[(int)position.x] = position;
    is_moving = true;
  }
  return coords;
}