#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"
#define PI 3.14159
#define GRAVITY 9.8
#define HORIZONTAL_STARTING_OFFSET 5
#define VERTICAL_STARTING_OFFSET (8 + MAP_HEIGHT)
#define TIME_INTERVAL 0.1

bool inMap(coordinate position) {
  return position.x >= 0 && position.y <= MAP_HEIGHT && position.x <= MAP_WIDTH;
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

void printXY(coordinate coord) {
  printf("(%d,%d)\n", (int) coord.x, (int)coord.y);
}

coordinate *parabola(player_input input) { // FIX: currently only works with 60 < angles < 90
  toRadians(&input);
 
  coordinate *coords = calloc(sizeof(coordinate), MAP_HEIGHT * MAP_WIDTH); //TODO: maxsize 
  coordinate position = {0, 0}; //TODO: turret pos - will be given

  double interval = 1 / (input.power * 0.5); 
  int coord = 0;
  for (double time = 0; inMap(position); time += interval) {
    
    position.x = HORIZONTAL_STARTING_OFFSET + getX(input.power, input.angle, time);
    position.y = VERTICAL_STARTING_OFFSET - getY(input.power, input.angle, position.x);
    printXY(position);
    coords[coord] = position;
    coord++;
  }

  return coords;
}

void printParabola(char map[MAP_HEIGHT][MAP_WIDTH], coordinate points[]) {
 // printCoordinates(points);
    for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; i++) {
        char *ch = &map[(int) points[i].y][(int) points[i].x];
        if ( *ch == '#') {
            break;
        } else if (*ch == ' ') {
              *ch = '.';
        }
    }
    printMap(map);
}