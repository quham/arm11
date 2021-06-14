#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '
#define TRAIL_CHR '.'

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT * MAP_WIDTH];
  coords[0] = player.curr_position;
  parabola(input, coords);
<<<<<<< HEAD
  printf("parab");
  for (int i = 1; coords[i].x != -1; i++) {//condition for for loop? add skip
=======
  for (int i = 1; coords[i].x != -1; i++) {  // condition for for loop? add skip
>>>>>>> de3fcf0b362ac0caa2deac2b2bce036d2f7499ed
    isTankCollision(coords[i]);
    updateCoord(BOMB_CHR, coords[i]);
    updateCoord(TRAIL_CHR, coords[i - 1]);
  }
}

<<<<<<< HEAD
void updateCoord(char c, coordinate p){
  map[p.y][p.x] = c;
=======
void updateCoord(char c, coordinate p) {
  map[p.x][p.y] = c;
>>>>>>> de3fcf0b362ac0caa2deac2b2bce036d2f7499ed
}

// player* nextPlayer(player* p) {
//   return (p == &player_1) ? &player_2 : &player_1;
// }

bool isTankCollision(coordinate c) {  // make 90 invalid angle;
  int x1 = player_1.curr_position.x;
  int x2 = player_2.curr_position.x;
<<<<<<< HEAD
  if (map[c.y][c.x] != '#' && map[c.y][c.x] != ' '){
=======
  if (map[c.x][c.y] != '#' && map[c.x][c.y] != ' ') {
>>>>>>> de3fcf0b362ac0caa2deac2b2bce036d2f7499ed
    if (abs(c.x - x1) < abs(c.x - x2)) {
      player_1.health -= 10;
    } else {
      player_2.health -= 10;
    }
    return true;
  }
  return false;
}
