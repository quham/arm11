#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void printState(State* state) {
  word32* regs = state->regs;

  printf("Registers:\n");
  for (int i = 0; i <= 12; i++) {  // iterate numbered registers
    printf("$%-3d: %10d (0x%08x)\n", i, regs[i], regs[i]);
  }
  printf("PC  : %10d (0x%08x)\n", regs[PC_INDEX], regs[PC_INDEX]);
  printf("CPSR: %10d (0x%08x)\n", regs[CPSR_INDEX], regs[CPSR_INDEX]);
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMORY_SIZE / BYTES_PER_WORD; i += BYTES_PER_WORD) {
    word32 chunk = fetch(i, state);
    if (chunk != 0) {
      printf("0x%08lx: 0x", (long)i);
      for (int j = 0; j < BYTES_PER_WORD; j++) {
        printf("%02x", state->memory[i + j]);
      }
      printf("\n");
    }
  }
}

// loads bytes (stored in little endian) into a word (big-endian)
word32 fetch(word32 addr, State* state) {
  if (addressValid(addr)) {
    word32 word = 0;
    for (int i = 0; i < BYTES_PER_WORD; i++) {
      word |= (state->memory[addr + i]) << (BYTE_SIZE * i);
      // shift to place next byte
    }
    return word;
  }
  return 0;  // why is this here?
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
        return PROCESSING;  // can reach with invalid function
      }
    default:
      perror("Error: Invalid instruction type\n");  // doesn't catch all invalid functions
      exit(EXIT_FAILURE);
  }
}

void execute(itype type, State* state, word32* decoded, word32* fetched) {
  if (checkCond(*decoded, state)) {
    switch (type) {
      case PROCESSING:
        dataProcessing(*decoded, state);
        break;
      case MULTIPLY:
        multiply(*decoded, state);
        break;
      case TRANSFER:
        singleDataTransfer(*decoded, state);
        break;
      case BRANCH:
        branch(*decoded, state);
        *fetched = NOT_INIT;
        *decoded = NOT_INIT;
        break;
      default:
        exit(EXIT_SUCCESS);
    }
  }
}

void pipeline(State* state) {
  instr decoded = NOT_INIT;
  instr fetched = NOT_INIT;
  itype type = 0;
  while (type != TERMINATE) {
    if (decoded != NOT_INIT) {
      execute(type, state, &decoded, &fetched);
    }
    if (fetched != NOT_INIT) {
      decoded = fetched;
      type = decode(fetched);
    }
    fetched = fetch(state->regs[PC_INDEX], state);
    state->regs[PC_INDEX] += 4;
  }
  printState(state);
}
