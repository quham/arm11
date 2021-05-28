#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"
#include "check_condition.h"
#include "instr_decompose.h"

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
  State state = {{0}, {0}};
  fread(state.memory, sizeof(byte), MEMORY_SIZE, file);
  fclose(file);

  pipeline(&state);
  return EXIT_SUCCESS;
}
