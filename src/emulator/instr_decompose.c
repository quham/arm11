#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

bool checkBit(instr instruction, int bit_no) {
  return 1 & (instruction >> bit_no);
}

void setBit(word32 *word, int index, bool bit) {
  word = bit ? (*word | (1 << index)) : (*word & !(1 << index));
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
  word32 msb = 0;
  word32 mask = 1;
  for (i = 0; i < amount; i++) {
    msb = mask & *operand;
    printf("MSB is %d \n ", msb);
    *operand = (msb << (WORD_SIZE - 1)) | (*operand >> 1);
  }
}

word32 signExtend(word32 number, int no_of_bits) {
  word32 mask = (1 << (WORD_SIZE - no_of_bits) - 1) << no_of_bits ;
  return number | (number & (1 << (no_of_bits - 1)) ? mask : 0);
}

// Calculates the value of the operand2.
word32 getOperand(word32 instruction, bool is_immediate, State* state) {
  word32 operand;

  if (is_immediate) {
    operand = getBits(instruction, 0, 7);
    // rotateRight(&operand, ROTATION_MULTIPLIER * operandRotate());
  } else {
    operand = state->regs[getRm(instruction)];
    word32 shift = getBits(instruction, 4, 11);
    word32 bit4 = checkBit(shift, 0);
    word32 shift_type = getBits(shift, 5, 6);
    word32 shift_value;
    if (bit4) {
      shift_value = state->regs[getRs(instruction)];
    } else {
      shift_value = getBits(instruction, 7, 11);
    }
    makeShift(&operand, shift_value, shift_type, instruction, state);
  }
  return operand;
}

// makes a shift of the operand2 depending on its shift_type
void makeShift(word32* operand, word32 shift_value, word32 shift_type, instr instruction,
               State* state) {
  // In case of register provided, selects its first byte.
  shift_value = shift_value & 0xff;
  bool carry_out = checkBit(*operand, shift_value - 1);

  switch (shift_type) {
    case 0:  // logic shift left
      carry_out = checkBit(*operand, WORD_SIZE - (int)shift_value);
      *operand <<= shift_value;
      break;
    case 1:  // logic shift right
      *operand >>= shift_value;
      break;
    case 2:  // arithmetic shift right
      *operand = signExtend(*operand, shift_value);
      break;
    case 3:  // rotate right
      rotateRight(operand, shift_value);
      break;
  }

  if (checkSet(instruction)) {
    word32* regs = state->regs;
      setBit(regs[CPSR_INDEX], 29, carry_out);
  }

  return;
}

// test functions
void decomp_tests() {
  instr test_instruction = 0xaf0c324e;

  instr bits_12_to_20 = 0xc3;  // inclusive
  if (getBits(test_instruction, 12, 20) == bits_12_to_20) {
    printf("getBits - pass\n");
  } else {
    printf("getBits - fail\n");
  }

  instr rd_bits = 0x3;
  if (getRd(test_instruction) == rd_bits) {
    printf("getRd - pass\n");
  } else {
    printf("getRd - fail\n");
  }

  instr cond_bits = 0xa;
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
