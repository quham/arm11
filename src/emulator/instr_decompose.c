#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

bool checkBit(instr instruction, int bit_no) {
  return (instruction & (word32)pow(2, bit_no)) >> bit_no;
}

bool checkImmediate(instr instruction) {
  return checkBit(instruction, 25);
}

bool checkSet(instr instruction) {
  return checkBit(instruction, 20);
}

// inclusive start_index, exclusive end_index
word32 getBits(instr instruction, int start_index, int end_index) {
  word32 mask = 0xffffffff >> (WORD_SIZE - (end_index - start_index));
  return (instruction >> start_index) & mask;
}

word32 condCode(instr instruction) {
  return getBits(instruction, 28, 32);
}

word32 getRs(instr instruction) {
  return getBits(instruction, 8, 12);
}

word32 getRm(instr instruction) {
  return getBits(instruction, 0, 4);
}

word32 getRd(instr instruction) {
  return getBits(instruction, 12, 16);
}

word32 getRn(instr instruction) {
  return getBits(instruction, 16, 20);
}

void rotateRight(word32* operand, int amount) {
  int i;
  word32 msb = 0b0;
  word32 mask = 1;
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

// test functions
void decomp_tests() {
  instr test_instruction = 0b10101111000011000011001001001110;

  instr bits_12_to_20 = 0b00000000000000000000000011000011;  // includsive
  if (getBits(test_instruction, 12, 20) == bits_12_to_20) {
    printf("getBits - pass\n");
  } else {
    printf("getBits - fail\n");
  }

  instr rd_bits = 0b0000000000000000000000000000011;
  if (getRd(test_instruction) == rd_bits) {
    printf("getRd - pass\n");
  } else {
    printf("getRd - fail\n");
  }

  instr cond_bits = 0b0000000000000000000000000001010;
  if (condCode(test_instruction) == cond_bits) {
    printf("condCode - pass\n");
  } else {
    printf("condCode - fail\n");
  }

  if (checkImmediate(test_instruction)) {
    printf("checkImmediate - pass\n");
  } else {
    printf("checkImmediate - fail\n");
  }
}