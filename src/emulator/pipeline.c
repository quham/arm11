#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void printState(State* state) {
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

word32 fetch(address addr, State* state) {
  //word32 word = state->memory[addr];
  word32 word = 0;
  for (int i = 0; i < BYTES_PER_WORD; i++) {
    word |= (state->memory[addr + i]) << (BYTE_SIZE * (BYTES_PER_WORD - (i + 1)));
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
        exit(EXIT_SUCCESS);
    }
  }
}

void pipeline(State* state) {
  instr decoded = NOT_INIT;
  instr fetched = NOT_INIT;
  itype type = 0;
  while (1) {
    if (type == TERMINATE) {
      printState(state);
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

