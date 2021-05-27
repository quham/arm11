#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

#define ROTATION_MULTIPLIER 2  // define in em_general.h

instr instruction = 0;
State *state;

void data_processing(word32 new_instruction, State *new_state) {
  instruction = new_instruction;
  state = new_state;
}

// int main(void) {
//   return 0;
// }

// Calculates the value of the operand2.
word32 getOperand(word32 instruction, State state) {
  word32 operand;

  if (checkImmediate(instruction)) {
    operand = getBits(instruction, 0, 7);
    rotateRight(&operand, ROTATION_MULTIPLIER * operandRotate());
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
    makeShift(&operand, shift_value, shift_type);
  }
  return operand;
}

// makes a shift of the operand2 depending on its shift_type
void makeShift(word32 *operand, word32 shift_value, word32 shift_type) {
  // In case of register provided, selects its first byte.
  shift_value = shift_value & 0xff;
  bool carry_out = checkBit(*operand, shift_value - 1);

  switch (shift_type) {
    case 0:  // logic shift left
      carry_out = checkBit(*operand, WORD_SIZE - (int) shift_value);
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
    word32 *regs = state->regs;
    if (carry_out) {
      regs[CPSR_INDEX] = regs[CPSR_INDEX] | 0x20000000; // sets C flag to 1
    } else {
      regs[CPSR_INDEX] = regs[CPSR_INDEX] & 0xd0000000; // sets C flag to 0
    }
  }

  return;
}

void performOperation(void) {
  word32 result;
  word32 opcode = getBits(instruction, 21, 24);
  word32 operand2 = getOperand();
  word32 rn = state->regs[getBits(instruction, 15, 19)];  // can we use getRn here?
  word32 *rd = state->regs + getBits(instruction, 16, 19);
  //  word32 carry_out = checkBit(state->regs[CPSR_INDEX], 31);

  switch (opcode) {
    case 0:  // 0000 and
      result = rn & operand2;
      *rd = result;
      break;
    case 1:  // 0001 eor
      result = rn ^ operand2;
      *rd = result;
      break;
    case 2:  // 0010 sub
      result = rn - operand2;
      *rd = result;
      break;
    case 3:  // 0011 rsb
      result = operand2 - rn;
      *rd = result;
      break;
    case 4:  // 0100 add
      result = rn + operand2;
      *rd = result;
      break;
    case 8:  // 1000 tst
      result = rn & operand2;
      break;
    case 9:  // 1001 teq
      result = rn ^ operand2;
      break;
    case 10:  // 1010 cmp
      result = rn - operand2;
      break;
    case 12:  // 1100 orr
      result = rn | operand2;
      *rd = result;
      break;
    case 13:  // 1101 mov
      result = operand2;
      *rd = result;
      break;
  }

  /*
  if (checkSet(instruction)) {
    char Z = (result == 0) ? 1 : 0;
    char N = checkBit(result, 31);
    check for overflow here (or in the add related cases)

    May look up conditions in comp arch;
  */
  return;
}
