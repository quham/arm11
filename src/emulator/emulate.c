#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

int main(int argc, char **argv) {
  // number of arguments main takes
  if (argc != 2) {
    perror("Error: Invalid arguments\n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  file = fopen(argv[1], "rb");

  if (file == NULL) {
    perror("Error: File is null\n");
    exit(EXIT_FAILURE);
  }

  // byte addressable memory
  State state = {{0}, {0}};
  fread(state.memory, BYTE_SIZE, MEMORY_SIZE, file);
  fclose(file);

  pipeline(&state);
  return EXIT_SUCCESS;
}
