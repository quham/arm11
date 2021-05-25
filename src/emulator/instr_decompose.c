#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "em_general.h"


uint32_t getBits(uint32_t instruction, uint32_t mask, int shiftNo) {
  uint32_t bits = instruction & mask;
  return bits >> shiftNo;
}

uint32_t getRn(instr instruction) {
  uint32_t mask = 0xf0000;
  return getBits(instruction, mask, 16);
}


uint32_t getRd(instr instruction) {
  uint32_t mask = 0xf000;
  return getBits(instruction, mask, 12);
}

void rotateRight(uint32_t* operand, int amount) {
  int i;
  uint32_t msb = 0b0;
  uint32_t mask = 1;
  printBits(*operand);
  printBits(mask);
  for (i = 0; i < amount; i++) {
    msb = mask & *operand;
    printf("MSB is %d \n ", msb);
    *operand = (msb << 31) | (*operand >> 1);
  }
}

uint32_t checkSet(instr instruction) {
  uint32_t mask = 0x100000;
  return getBits(instruction, mask, 20);
}

