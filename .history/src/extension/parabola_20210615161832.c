#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

bool isCollision(coordinate coord) {
  return !aboveMap(coord) && (map[coord.y][coord.x] == '#' || isTankCollision(coord));
}

// TODO: fix
bool isTankCollision(coordinate coord) {
  int x1 = player_1.curr_coord.x;
  int x2 = player_2.curr_coord.x;
  char ch = map[coord.y][coord.x];
  printf("%c",ch);
  if (ch == '#' || ch == ' ') {
    return false;
  }
  if (abs(coord.x - x1) < abs(coord.x - x2)) {
    player_1.health -= 10;
  } else {
    player_2.health -= 10;
  }
  return true;
  
}

// TODO: compute correct coords when player 2 is shooting
double getY(double initial_velocity, double angle, double time) {
  return sin(angle) * initial_velocity * time - GRAVITY * pow(time, 2) / 2;
}

double getX(double initial_veloctiy, double angle, double time) {
  return (initial_veloctiy * time * cos(angle));
}

double toRadians(player_input *input) {
  return (input->angle * PI) / 180;
}

void parabola(player_input input, coordinate *coords) {
  double angle = toRadians(&input);

  coordinate coord = coords[1];
  const coordinate start_coord = coords[0];

  double interval = 1 / (input.power * 0.5);
  int i = 1;
  for (double time = interval; inBounds(coord) && !isCollision(coord); time += interval, i++) {
    coord.y = start_coord.y - getY(input.power, angle, time);
    coord.x = start_coord.x + getX(input.power, angle, time);
    coords[i] = coord;
  }
  coords[i - 1] = TERM_COORD;
}
