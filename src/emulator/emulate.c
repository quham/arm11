#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"
#include "check_condition.h"
#include "instr_decompose.h"

void printStateTEST(State* state) {
  word32 *regs = state->regs;

  printf("Registers:\n");
  for (int i = 0; i <= 12; i++) {  // iterate numbered registers
   printf("$%3d:%10d (0x%08x) \n", i, regs[i], regs[i]);
  }
  printf("PC  :%10d (0x%08x) \n", regs[PC_INDEX], regs[PC_INDEX]);
  printf("CSPR:%10d (0x%08x) \n", regs[CPSR_INDEX], regs[CPSR_INDEX]);
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMORY_SIZE / 4; i++) {
    word32 chunk = fetch(4 * i, state);
    if (chunk != 0) {
     printf("0x%08lx: 0x%x\n", sizeof(i) * i  , chunk);
    } 
  }
}

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
  printStateTEST(&state); 
  fclose(file);

  pipeline(&state);
  return EXIT_SUCCESS;
}
