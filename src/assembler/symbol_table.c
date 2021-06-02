#include <stdio.h>
#include <string.h>

#include "ass_general.h"

void up(char *ch) {
  *ch -= 'a';
}

void succ(int *n) {
  *n = *n + 1;
}

void ups(char str[]) {
  for (; *str; str++) {
    up(&str[0]);
  }
}

int main() {
  char str[10] = {'h', 'e', 'l', 'l', 'o'};
  ups(str);
  printf("%s", str);
  // char ch = 'c';
  // up(&ch);
  // printf("%c\n", ch);
  // int n = 5;
  // succ(&n);
  // printf("%d\n", n);
  return 0;
}
