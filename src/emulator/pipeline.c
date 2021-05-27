#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void printRegisters(struct State* state) {
  for (int i = 0; i <= 12; i++) {  // amount of numbered registers
    printf("R%d: %d\n", i, state->regs[i]);
  }
  printf("SP: %d\n", state->regs[SP_INDEX]);
  printf("LP: %d\n", state->regs[LP_INDEX]);
  printf("PC: %d\n", state->regs[PC_INDEX]);
  printf("CSPR: %d\n", state->regs[CPSR_INDEX]);
}

instr fetch(word32 pc, State* state) {
  return state->memory[pc];
}


enum itype decode(instr instruction) {  // return type?
  switch (getBits(instruction, 26, 27)) {
    case 2:
      return BRANCH;
    case 1:
      return TRANSFER;
    case 0:
      if (!getBits(instruction, 22, 25) && !(getBits(instruction, 4, 7) ^ 1001)) {
        // extracts bits 4-7 xor with 1001 to check for multiply format
        return MULTIPLY;
      } else if (!instruction) {
        return TERMINATE;
      } else {
        return PROCESSING;
      }
    default:
      perror("Invalid instruction type"); 
      exit(EXIT_FAILURE);
  }
}

void execute(instr instruction, enum itype type, struct State* state, word32* decoded,
               word32* fetched) {
  if (checkCond(instruction, state)) {
    switch (type) {
      case PROCESSING:
        data_processing(instruction, state);
        break;
      case MULTIPLY:
        multiply(instruction, state);
        break;
      case TRANSFER:
        single_data_transfer(instruction, state);
        break;
      case BRANCH:
        branch(instruction, state);
        *decoded = NOT_INIT;
        *fetched = NOT_INIT;
        break;
      default:
        printRegisters(state);
        exit(EXIT_SUCCESS);  // exits function? should i print here?
    }
  }
}

void pipeline(State* state) {
  instr decoded = NOT_INIT;
  instr fetched = NOT_INIT;
  enum itype type;
  while (1) {
    if (decoded != NOT_INIT) {
      execute(decoded, type, state, &decoded, &fetched);
    }
    if (fetched != NOT_INIT) {
      decoded = fetched;
      type = decode(fetched);
    }
    fetched = fetch(state->regs[PC_INDEX], state);
    state->regs[PC_INDEX] += 4;
  }
}
