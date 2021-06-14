#include <stdbool.h>
#include <stdio.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '
#define TRAIL_CHR '.'

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT*MAP_WIDTH]; 
  coords[0] = player.curr_position;
  parabola(input, coords);
  for (int i = 1; coords[i].x != -1; i++) {//condition for for loop? add skip
    isTankCollision(coords[i],*nextPlayer(player));
    updatePoint(BOMB_CHR, coords[i]);
    updatePoint(TRAIL_CHR, coords[i - 1]);
  }
  return true;
}

void updateCoord(char c, coordinate p){
  map[p.x][p.y] = c;
}

player* nextPlayer(player* p) { 
  return (p == &player_1) ? &player_2 : &player_1;
}

bool isTankCollision(coordinate c,player p){//make 90 invalid angle;
  if (map[c.x][c.y] != '#' && map[c.x][c.y] != ' '){
    p.health -= 10;
    return true;
  }
  return false;
} 

void initTanks(void){
  map[5][32] = '|';

}
