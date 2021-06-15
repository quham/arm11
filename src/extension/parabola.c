#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

bool isCollision(coordinate coord) {
  return !aboveMap(coord) && (map[coord.y][coord.x] == '#' || isTankCollision(coord));
}

// TODO: compute correct coords when player 2 is shooting
double getY(double initial_velocity, double angle, double time) {
  return sin(angle) * initial_velocity * time - GRAVITY * pow(time, 2) / 2;
}

double getX(double initial_veloctiy, double angle, double time) {
  return (initial_veloctiy * time * cos(angle));
}

void toRadians(player_input *input) {
  input->angle = (input->angle * PI) / 180;
}

void parabola(player_input input, coordinate *coords) {
  toRadians(&input);

  coordinate coord = coords[0];
  const coordinate start_coord = coords[0];

  double interval = 1 / (input.power * 0.5);
  int i = 1;
  for (double time = interval; inBounds(coord) && !isCollision(coord); time += interval, i++) {
    double x = getX(input.power, input.angle, time);
    coord.y = start_coord.y - getY(input.power, input.angle, time);
    coord.x = start_coord.x + x;
    coords[i] = coord;
  }
  coords[i - 1] = TERM_COORD;
}
