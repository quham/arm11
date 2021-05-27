#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "branch.c"
#include "check_condition.c"
#include "data_processing.c"
#include "em_general.h"
#include "instr_decompose.c"
#include "multiply.c"
#include "pipeline.c"
#include "single_data_transfer.c"

int main(int argc, char **argv) {
  decomp_tests();  // temp test code
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
