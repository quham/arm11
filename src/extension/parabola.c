#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"
#define PI  3.14159
#define GRAVITY 9.8

bool inMap(coordinate position) {
  return position.x >= 0 && position.y >= 0 && position.x <= MAP_WIDTH;
}

void printCoordinates(coordinate *coords) {
  while (inMap(coords[0])) {
    printf("(%d,%d)\n", (int)coords->x, (int)coords->y); 
    coords++;
  }
}

double getY(double initial_velocity, double angle, double x) {
  return ((x * tan(angle)) - ((GRAVITY * pow(x, 2) * (1 + pow(tan(angle), 2)) / (2 * pow(initial_velocity, 2)))));
}

double getX(double initial_veloctiy, double angle, double time) {
  return (initial_veloctiy * time * cos(angle));
}

void toRadians(player_input *input) {
  input->angle = (input->angle * PI) / 180;
}

coordinate *parabola(player_input input) {
  toRadians(&input);
 
  coordinate *coords = malloc(sizeof(coordinate) * MAP_HEIGHT * MAP_WIDTH); //TODO: maxsize 
  coordinate position = {0, MAP_HEIGHT}; //TODO: turret pos - will be given

  int coord = 0;
  for (double time = 0; inMap(position); time+=0.1) {
    position.x = getX(input.power, input.angle, time);
    position.y = MAP_HEIGHT - getY(input.power, input.angle, position.x);
    coords[coord] = position;
    coord++;
  }

  return coords;
}

void printParabola(char map[MAP_HEIGHT][MAP_WIDTH], coordinate points[]) {
    for (int i = 0; i < 50; i++) {
        map[(int) points[i].y][(int) points[i].x] = '.';
    }
    printMap(map);
}