#include <stdbool.h>
#include <stdio.h>
#define MAX_POWER 10
#define BOMB_CHR '@'
#define EMPTY_CHR ' '

typedef enum player { A, B } player;
typedef struct point {
  int x;
  int y;
} point;

// player curr_player = A;
// void swapPlayer(void) {  // or takes current player?
//   if (curr_player == A) {
//     curr_player = B;
//   } else {
//     curr_player = A;
//   }
// }

// bool playerTurn(player cplayer) {
//   float angle = 0;
//   int power = 0;
//   printf("Enter shot angle: ");  // what if not a number?
//   scanf("%f", &angle);
//   printf("Enter shot power between 1-10: ");
//   scanf("%d", &power);
//   if (power < 1 || power > 10) {
//     perror("power must be between 1-10!");
//   }
//   point* points = parabola(angle, power);
//   for (int i = 1; points != NULL; i++) {
//     // if (collision())
//     updatePoint(BOMB_CHR, points[i]);
//     updatePoint(EMPTY_CHR, points[i - 1]);
//   }
//   swapPlayer();  // player global variable?
// }
