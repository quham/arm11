#include <stdbool.h>
#include <stdio.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '

void playerTurn(player player, player_input input) {
  player_input input = getPlayerInput();
  coordinate coords[MAP_HEIGHT*MAP_WIDTH]; //replace with MAX_COORDS const
  parabola(input, coords);//change parab to take player use start pos
  for (int i = 1; coords != NULL; i++) {
    if (isTankCollision(coords[i])){
      
      //check input bomb type for extension vary health accoordingly switch statement
    }
    updatePoint(BOMB_CHR, coords[i]);
    updatePoint(EMPTY_CHR, coords[i - 1]);
  }
  curr_player = nextPlayer();  // player global variable?
  return true;
}

void updateCoord(char c, coordinate p){
  map[p.x][p.y] = c;
}

// player* nextPlayer(void) { 
//   if (curr_player == &player1) {
//     return &player2;
//   } else {
//     return &player1;
//   }
// }

bool isTankCollision(){
  if (tankA){
      //nextPlayer()->health -= 10;
  }
  health-1
} 

void initTanks(void){

}
