#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

void parabola(player_input input, coordinate *coords) {

    const double angle = toRadians(&input);
    const coordinate start_coord = coords[0];
    const double interval = 1 / (input.power * 0.75);  // magic number

    coordinate coord = coords[1];
    int i = 1;
    for (double time = interval; !isCollision(coord); time += interval, i++) {
        coord.y = start_coord.y - getY(input.power, angle, time);
        coord.x = start_coord.x + getX(input.power, angle, time);
        coords[i] = coord;
    }
    coords[i - 1] = TERM_COORD;
}

double toRadians(player_input *input) {
    return input->angle * PI / 180;
}

double getY(double initial_velocity, double angle, double time) {
    return sin(angle) * initial_velocity * time - GRAVITY * pow(time, 2) / 2;
}

double getX(double initial_veloctiy, double angle, double time) {
    return cos(angle) * initial_veloctiy * time;
}

bool isCollision(coordinate coord) {
    return !inBounds(coord) || (!aboveMap(coord) && (isMapCol(coord) || isTankCol(coord)));
}

bool isMapCol(coordinate coord) {
    return map[coord.y][coord.x] == '#';
}

bool isTankCol(coordinate coord) {
    if (map[coord.y][coord.x] == ' ') {
        return false;
    }
    const int x1 = player_1.curr_coord.x;
    const int x2 = player_2.curr_coord.x;
    if (abs(coord.x - x1) < abs(coord.x - x2)) {
        player_1.health -= SHOT_DAMAGE;
    } else {
        player_2.health -= SHOT_DAMAGE;
    }
    return true;
}
