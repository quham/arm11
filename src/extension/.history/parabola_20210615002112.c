#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"
#define PI 3.14159
#define GRAVITY 9.8
#define TIME_INTERVAL 0.1

bool inMap(coordinate position) {
  return position.x >= 0 && position.x <= MAP_WIDTH;
}

bool isCollision(coordinate position) {
  return position.y >= 0 && map[position.y][position.x] == '#';
}

void printCoordinates(coordinate *coords) {
  while (inMap(coords[0])) {
    printf("(%d,%d)\n", (int)coords->x, (int)coords->y);
    coords++;
  }
}

double getY(double initial_velocity, double angle, double x) {
  return ((x * tan(angle)) -
          ((GRAVITY * pow(x, 2) * (1 + pow(tan(angle), 2)) / (2 * pow(initial_velocity, 2)))));
}

double getX(double initial_veloctiy, double angle, double time) {
  return (initial_veloctiy * time * cos(angle));
}

void toRadians(player_input *input) {
  input->angle = (input->angle * PI) / 180;
}

void printXY(coordinate coord) {
  printf("(%d,%d)\n", coord.x, coord.y);
}

void parabola(player_input input,
              coordinate *coords) {  // FIX: currently only works with 60 < angles < 90
  toRadians(&input);

  coordinate position = coords[0];  // TODO: turret pos - will be given
  printXY(position);

  double interval = 1 / (input.power * 0.5);
  int coord = 1;
  for (double time = 0; inMap(position) && isCollision(position); time += interval) {
    double x = getX(input.power, input.angle, time);
    position.y = coords[0].y - getY(input.power, input.angle, x);
    position.x = coords[0].x + x;
    printXY(position);
    coords[coord] = position;
    coord++;
  }
  printf("TEST\n");
  coordinate c ;
  c.x = -1;
  c.y = -1;
  printf("done");
  coords[coord - 1] = c;
  printf("done");
}

void printParabola(coordinate points[]) {
  // printCoordinates(points);

  for (int i = 0; points[i].x != -1; i++) {
    printXY(points[i]);
    if (points[i].y >= 0) {
      map[points[i].y][points[i].x] = '.';
    }
  }
  printMap();
}
