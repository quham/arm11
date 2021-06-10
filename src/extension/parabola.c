#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "worms.h"
#define PI 3.142857

double getY(double x, double angle, double u) {
	return ((x * tan(angle)) - ((9.8 * pow(x, 2) * (1 + pow(tan(angle), 2)) / (2 * pow(u, 2)))));
}

player_input toRadians(player_input input) {
	input.angle = (input.angle * PI) / 180;
	return input;
}

coordinate *parabola(player_input input) {
	input = toRadians(input);

	coordinate *coords = malloc(sizeof(coordinate) * 128 * 2);
	coordinate position = {0, 0};
	bool is_moving = false;
	while (position.y > 0 || !is_moving) {
		position.x++;
		position.y = getY(position.x, input.angle, input.power);
		
		coords[(int) position.x] = position;
		is_moving = true;
	}
	return coords;
}