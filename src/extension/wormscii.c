#include <stdio.h>
#include "worms.h"

int main(void) {


    printf("                                    \n");
    printf("      ~^~@  WELCOME TO WORMSCII  @~^~\n");
    printf("\n");
    printf(" *~       HELP THE WORLD RECOVER  ~*     \n");
    printf("   ~*  EXTERMINATE MISBEHAVING WORMS  *~ \n\n");


    //INTRODUCTION / GAME RULES ??


    /* ENTER GAME LOOP */
    player_input input = {45, 30};
    coordinate * curve = parabola(input);
    for (int i = 0; i < 128; i ++) {
        printf("(%d , %d)\n", curve->x, curve->y);
        curve++;
    }

}