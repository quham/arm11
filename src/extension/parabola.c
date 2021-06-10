#include <stdio.h>
#include <math.h>

#include "worms.h"


double getY(double x, double angle, double u) {
	return (x * tan(angle) - 9.8 * pow(x, 2) * ((1 + pow(tan(angle), 2) / (2 * pow(u, 2)))));
}

coordinate *parabola(player_input input) {
	coordinate coords[128] = {0};
	coordinate position = {0, 0};
	while (position.y > 0) {
		position.y = getY(position.x, input.angle, input.power);
		position.x++;
		coords[position.x] = position;
	}
	return coords;
}