#include <stdio.h>
#include "worms.h"
#include <math.h>
#include "pbPlot/pbPlots.h"
#include "pbPlot/supportLib.h"

int main(void) {


    printf("                                    \n");
    printf("      ~^~@  WELCOME TO WORMSCII  @~^~\n");
    printf("\n");
    printf(" *~       HELP THE WORLD RECOVER  ~*     \n");
    printf("   ~*  EXTERMINATE MISBEHAVING WORMS  *~ \n\n");


    //INTRODUCTION / GAME RULES ??


    /* ENTER GAME LOOP */
    player_input input = {40, 60};
    coordinate * curve = parabola(input);
    // double x[256] = {0};
    // double y[256] = {0};
    for (int i = 0; i < 128 * 2; i ++) {
        printf("(%d , %d)\n", (int) (curve->x), (int) (curve->y));
        // x[i] = curve->x;
        // y[i] = curve->y;
        curve++;

        if (curve->x == 0 && curve->y == 0) {
            break;
        }
    }

    // RGBABitmapImageReference * imageRef = CreateRGBABitmapImageReference();

    // DrawScatterPlot(imageRef, 600, 400, x, 256, y, 256);

    // size_t length;
    // double *pngData = ConvertToPNG(&length, imageRef->image);
    // WriteToFile(pngData, length, "parabola.png");


}