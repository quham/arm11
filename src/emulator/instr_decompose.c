#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

word32 getBits(instr instruction, word32 mask, int shiftNo) {
  word32 bits = instruction & mask;
  return bits >> shiftNo;
}

word32 getBit(instr instruction, int bitNo) {
  return (instruction & (word32)pow(2, bitNo)) >> bitNo;
}

word32 condCode(instr instruction) {
  return getBit(instruction, COND_CODE_INDEX);
}

word32 checkImmediate(instr instruction) {
  return getBit(instruction, CHECK_IMM_INDEX);
}

word32 checkSet(instr instruction) {
  return getBit(instruction, CHECK_SET_INDEX);
}

word32 getRs(instr instruction) {
  return getBits(instruction, RS_MASK, RS_INDEX);
}

word32 getRm(instr instruction) {
  return getBits(instruction, RM_MASK, RM_INDEX);
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
word32 signExtend(word32 number , int noOfBits){
    word32 mask = ((word32) pow( 2, noOfBits + 1) - 0.5) ;//0.5 accounts for double inconsistency of rounding across different architectures
    mask = mask << (32 - noOfBits - 1);
    return number | (number & (1 << (noOfBits-1)) ? mask : 0);
}
