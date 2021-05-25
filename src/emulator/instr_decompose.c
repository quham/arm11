#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "em_general.h"

word32 getBits(instr instruction, word32 mask, int shiftNo) {
  word32 bits = instruction & mask;
  return bits >> shiftNo;
}

word32 condCode(instr instruction) {
  return getBits(instruction, COND_CODE_MASK, COND_CODE_INDEX);
}

word32 checkImmediate(instr instruction) {
  return getBits(instruction, CHECK_IMM_MASK, CHECK_IMM_INDEX);
}

word32 checkSet(instr instruction) {
  return getBits(instruction, CHECK_SET_MASK, CHECK_SET_INDEX);
}

void rotateRight(word32* operand, int amount) {
  int i;
  word32 msb = 0b0;
  word32 mask = 1;
  printBits(*operand);
  printBits(mask);
  for (i = 0; i < amount; i++) {
    msb = mask & *operand;
    printf("MSB is %d \n ", msb);
    *operand = (msb << 31) | (*operand >> 1);
  }
}
