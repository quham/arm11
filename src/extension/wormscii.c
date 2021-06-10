#include <stdio.h>
#include "worms.h"
#include <math.h>

int main(void) {


    printf("                                    \n");
    printf("      ~^~@  WELCOME TO WORMSCII  @~^~\n");
    printf("\n");
    printf(" *~       HELP THE WORLD RECOVER  ~*     \n");
    printf("   ~*  EXTERMINATE MISBEHAVING WORMS  *~ \n\n");


    //INTRODUCTION / GAME RULES ??


    /* ENTER GAME LOOP */
    player_input input = {55, 40};
    coordinate * curve = parabola(input);
    for (int i = 0; i < 128 * 2; i ++) {
        printf("(%d , %d)\n", (int) (curve->x), (int) (curve->y));
        curve++;
        if (curve->x == 0 && curve->y == 0) {
            break;
        }
    }

}