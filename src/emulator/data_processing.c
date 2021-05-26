#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "em_general.h"
#include "instr_decompose.c"

#define ROTATION_MULTIPLIER 2

instr instruction = 0;

void data_processing(word32 new_instruction, struct State *state) {
  instruction = new_instruction;
  //  word32 opcode = getOpcode(instruction);
  /*  word32 operdan2;
  if (checkImmediate(instruction)) {
    operand2 = operandImmediate(instruction);
    }*/
}

int main(void) {
  instr instruction = 0b00000010101101010101000000000000;
  // data_processing(instruction);
  word32 s = checkSet(instruction);
  word32 i = checkImmediate(instruction);
  word32 opcode = getOpcode();
  word32 rn = getRn(instruction);
  word32 rd = getRd(instruction);
  
  printf("Instruction is: ");
  printBits(instruction);
  printf("Immediate value is: ");
  printBits(i);
  printf("S value is: ");
  printBits(s);
  printf("Opcode is: ");
  printBits(opcode);
  printf("Rn is: ");
  printBits(rn);
  printf("Rd is: ");
  printBits(rd);
  rotateRight(&rd, 4);
  printf("Rd rotated is: ");
  printBits(rd);
  return 0;
}

word32 getOpcode(void) {
  return getBits(instruction, OPCODE_MASK, OPCODE_INDEX);
}

word32 operandRotate(void) {
  return getBits(instruction, OPERAND_ROTATE_MASK, OPERAND_ROTATE_INDEX);
}

word32 operandImmediate(void) {
  return getBits(instruction, OPERAND_IMM_MASK, OPERAND_ROTATE_INDEX);
}

word32 operandShift(void) {
  return getBits(instruction, OPERAND_SHIFT_MASK, OPERAND_SHIFT_INDEX);
}

word32 operandRm(void) {
  return getBits(instruction, OPERAND_RM_MASK, OPERAND_RN_INDEX);
}

word32 getRn(instr instruction) {
  return getBits(instruction, OPERAND_RN_MASK, OPERAND_RN_INDEX);
}

word32 getRd(instr instruction) {
  return getBits(instruction, OPERAND_RD_MASK, OPERAND_RD_INDEX);
}

//Calculates the value of the operand2.
word32 getOperand(void) {
  word32 operand;
  if (checkImmediate(instruction)) {
    operand = operandImmediate();
    rotateRight(&operand, ROTATION_MULTIPLIER * operandRotate());
  } else {
    operand = getRm(instruction); // Should get the register instead. Left for now.
    word32 shift = operandShift();
    //bit4 gets the value of the 4th bit in the operand2. It is LSB of shift
    word32 bit4 = getSpecificBit(shift, 0);
    //0x6 is the mask to get bits 5-6 of operand2, they are 1-2 of shift 
    word32 shift_type = getBits(shift, 0x6, 1);
    word32 shift_value;
    if (bit4) {
      shift_value = getRs(instruction); // should get the register instead. Left for now
    } else {
      shift_value = getBits(instruction, 0xf80, 7);
    }
    makeShift(&operand, shift_value, shift_type);
  }
  return operand;
}

// makes a shift of the operand2 depending on its shift_type
void makeShift(word32 *operand, word32 shift_value, word32 shift_type) {
  //In case of register provided, select first byte of the shift_value
  shift_value = shift_value & 0xff;
  word32 carry_out = getSpecificBit(*operand, shift_value); // consider some edge cases here (eg shift_value > 32)
 
  switch(shift_type) {
  case 0 :// logic shift left
    *operand <<= shift_value;
    carry_out = 31 - shift_value;
    break;
  case 1 :// logic shift right
    *operand >>= shift_value;
    break;
  case 2 :// arithmetic shift right
   *operand = signExtend(*operand, shift_value);
    break;
  case 3 :// rotate right
    rotateRight(operand, shift_value);
    break;
  }
  // assign here carry_out bit
  return;
}

  
void printBits(word32 x) {
  int i;
  word32 mask = 1 << 31;
  for(i=0; i<32; ++i) {
    if (i % 4 == 0)
      printf(" ");
    printf("%i", (x & mask) != 0);
    x <<= 1;
  }
  printf("\n ");
}
