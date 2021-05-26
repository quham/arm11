#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

word32 getBits(instr instruction, word32 mask, int shift_no) {
  word32 bits = instruction & mask;
  return bits >> shift_no;
}

word32 getBits(instr instruction, int start_index, int end_index) {
  word32 mask = 0xffffffff >> (WORD_SIZE - (end_index - start_index));
  return (instruction >> start_index) & mask;
}

word32 condCode(instr instruction) {
  return checkBit(instruction, 28);
}

word32 checkImmediate(instr instruction) {
  return checkBit(instruction, 25);
}

word32 checkSet(instr instruction) {
  return checkBit(instruction, 20);
}

word32 getRs(instr instruction) {
  return getBits(instruction, 12, 8);
}

word32 getRm(instr instruction) {
  return getBits(instruction, 4, 0);
}

void rotateRight(word32 *operand, int amount) {
  int i;
  word32 msb = 0b0;
  word32 mask = 1;
  printBits(*operand);
  printBits(mask);
  for (i = 0; i < amount; i++) {
    msb = mask & *operand;
    printf("MSB is %d \n ", msb);
    *operand = (msb << (WORD_SIZE - 1)) | (*operand >> 1);
  }
}
word32 signExtend(word32 number, int no_of_bits) {
  word32 mask = ((word32)pow(2, no_of_bits + 1) - ROUNDING_ERROR);
  mask = mask << (WORD_SIZE - no_of_bits - 1);
  return number | (number & (1 << (no_of_bits - 1)) ? mask : 0);
}
