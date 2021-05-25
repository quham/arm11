#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "em_general.h"
#include "instr_decompose.c"

#define ROTATION_MULTIPLIER

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
  data_processing(instruction);
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
  word32 mask = 0x1e00000;
  return getBits(instruction, mask, 21);
}

word32 operandRotate(void) {
  word32 mask = 0xf00;
  return getBits(instruction, mask, 8);
}

word32 operandImmediate(void) {
  word32 mask = 0xff;
  return getBits(instruction, mask, 0);
}

word32 operandShift(void) {
  word32 mask = 0xff0;
  return getBits(instruction, mask, 4);
}

word32 operandRm(void) {
  word32 mask = 0xf;
  return getBits(instruction, mask, 0);
}

word32 getRn(instr instruction) {
  word32 mask = 0xf0000;
  return getBits(instruction, mask, 16);
}

word32 getRd(instr instruction) {
  word32 mask = 0xf000;
  return getBits(instruction, mask, 12);
}

/*
word32 getOperand(void) {
  word32 operand;
  int rotation;
  if (checkImmediate()) {
    operand = operandImmediate();
    rotateRight(&operand, ROTATION_MULTIPLIER * operandRotate());
  } else {
    //operand = 
  }
  return operand;
}
*/

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
