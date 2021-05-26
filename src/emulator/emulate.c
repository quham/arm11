#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

// print for debugging

int main(int argc, char **argv) {
  if (argc != 2) {
    perror("Invalid arguments! \n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  file = fopen(argv[1], "rb");

  if (file == NULL) {
    perror("File is null! \n");
    exit(EXIT_FAILURE);
  }

  // byte addressable memory
  word32 memory[MEMORY_SIZE] = {0};
  fread(memory, sizeof(word32), MEMORY_SIZE, file);
  fclose(file);
  word32 regs[NUMBER_OF_REGISTERS];
  word32 memory[MEMORY_SIZE];
  struct State state = {regs, memory};
  pipeline(state);
  return EXIT_SUCCESS;
}
