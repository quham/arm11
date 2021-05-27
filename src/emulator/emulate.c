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
  word32 memory[MEMORY_SIZE] = {0};
  fread(memory, sizeof(word32), MEMORY_SIZE, file);
  fclose(file);
  word32 regs[NUMBER_OF_REGISTERS] = {0};

  struct State state = {regs, memory};
  pipeline(&state);
  return EXIT_SUCCESS;
}
