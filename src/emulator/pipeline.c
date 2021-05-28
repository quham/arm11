#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void printRegisters(State* state) {
  printf("Registers:\n");
  for (int i = 0; i <= 12; i++) {  // iterate numbered registers
    if (i == 10 || i == 11 || i == 12) {
    printf("$%d :         %d (0x%08x) \n", i, state->regs[i], state->regs[i]);  
    } else {
    printf("$%d  :         %d (0x%08x) \n", i, state->regs[i], state->regs[i]);
    }
  }
 // printf("SP  :         %d (0x%08x) \n", state->regs[SP_INDEX],  state->regs[SP_INDEX]);
 // printf("LP  :         %d (0x%08x) \n", state->regs[LP_INDEX], state->regs[LP_INDEX]);
  printf("PC  :         %d (0x%08x) \n", state->regs[PC_INDEX],  state->regs[PC_INDEX]);
  printf("CSPR:         %d (0x%08x) \n", state->regs[CPSR_INDEX], state->regs[CPSR_INDEX]);
  printf("Non-zero memory:\n");
  
}

word32 fetch(address addr, State* state) {
  word32 word = state->memory[addr];
  for (int i = 1; i < BYTES_PER_WORD; i++) {
    word |= (state->memory[addr + i]) << (BYTE_SIZE * i);
    // shift to place next byte
  }
  return word;
}

itype decode(instr instruction) {
  switch (getBits(instruction, 26, 28)) {
    case 2:
      return BRANCH;
    case 1:
      return TRANSFER;
    case 0:
      if (!getBits(instruction, 22, 26) && !(getBits(instruction, 4, 8) ^ 0x9)) {
        // bits 4 to 8 equal 0x9 in all multiply instructions
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

void execute(instr instruction, itype type, State* state, word32* decoded, word32* fetched) {
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
        exit(EXIT_SUCCESS);  // exits function? should i print here?
    }
  }
}

void pipeline(State* state) {
  instr decoded = NOT_INIT;
  instr fetched = NOT_INIT;
  itype type;
  while (1) {
    if (type == TERMINATE) {
      printRegisters(state);
      return;
    }
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

