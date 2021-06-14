#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '
#define TRAIL_CHR '.'

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT*MAP_WIDTH]; 
  coords[0] = player.curr_position;
  parabola(input, coords);
  for (int i = 1; coords[i].x != -1; i++) {//condition for for loop? add skip
    isTankCollision(coords[i]);
    updatePoint(BOMB_CHR, coords[i]);
    updatePoint(TRAIL_CHR, coords[i - 1]);
  }
}

void updateCoord(char c, coordinate p){
  map[p.x][p.y] = c;
}

// player* nextPlayer(player* p) { 
//   return (p == &player_1) ? &player_2 : &player_1;
// }

bool isTankCollision(coordinate c){//make 90 invalid angle;
  int x1 = player_1.curr_position.x;
  int x2 = player_2.curr_position.x;
  if (map[c.x][c.y] != '#' && map[c.x][c.y] != ' '){
    if (abs(c.x - x1) < abs(c.x - x2)) {
      player_1.health -=10;
    }else{
      player_2.health -=10;
    }
    return true;
  }
  return false;
} 


