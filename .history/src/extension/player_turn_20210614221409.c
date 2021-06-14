#include <stdbool.h>
#include <stdio.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '

void playerTurn(player player, player_input input) {
  coordinate coords[MAP_HEIGHT*MAP_WIDTH]; 
  coords[0] = player.curr_position;
  parabola(input, coords);
  for (int i = 1; coords[i].x != -1 i++) {//condition for for loop?
    isTankCollision(coords[i]);
    updatePoint(BOMB_CHR, coords[i]);
    updatePoint(EMPTY_CHR, coords[i - 1]);
  }
  curr_player = nextPlayer();  // player global variable?
  return true;
}

void updateCoord(char c, coordinate p){
  map[p.x][p.y] = c;
}

player* nextPlayer(player* p) { 
  return (p == &player_1) ? &player_2 : &player_1;
}

bool isTankCollision(coordinate c){//make 90 invalid angle;
  if (tankA){
      //nextPlayer()->health -= 10;
  }
  health-1
} 

void initTanks(void){
  map[5][32] = '|';

}
