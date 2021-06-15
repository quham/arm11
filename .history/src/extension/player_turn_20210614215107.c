#include <stdbool.h>
#include <stdio.h>

#include "worms.h"

#define BOMB_CHR '@'
#define EMPTY_CHR ' '

void playerTurn(player player, player_input input) {
  player_input input = getPlayerInput();
  coordinate coords[MAX_POINTS]; 
  parabola(input, coords);//change parab to take player use start pos
  for (int i = 1; points != NULL; i++) {
    if (isTankCollision(points[i])){
      
      //check input bomb type for extension vary health accoordingly switch statement
    }
    updatePoint(BOMB_CHR,'@', points[i]);
    updatePoint(EMPTY_CHR,'.' , points[i - 1]);
  }
  curr_player = nextPlayer();  // player global variable?
  return true;
}

void updatePoint(char c, coordinate p){
  map[p.x][p.y] = c;
}

// player* nextPlayer(void) { 
//   if (curr_player == &player1) {
//     return &player2;
//   } else {
//     return &player1;
//   }
// }

void playerTurn(player p) {
  player_input input = getPlayerInput();
  coordinate coords[MAX_POINTS]; 
  parabola(input, coords);//change parab to take player use start pos
  for (int i = 1; points != NULL; i++) {
    if (isTankCollision(points[i])){
      
      //check input bomb type for extension vary health accoordingly switch statement
    }
    updatePoint(BOMB_CHR,'@', points[i]);
    updatePoint(EMPTY_CHR,'.' , points[i - 1]);
  }
  curr_player = nextPlayer();  // player global variable?
  return true;
}
bool isTankCollision(){
  if (tankA){
      //nextPlayer()->health -= 10;
  }
  health-1
} 
