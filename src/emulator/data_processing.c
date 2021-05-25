
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "data_processing.h"
#define ROTATION_MULTIPLIER

uint32_t instruction;

void data_processing(uint32_t new_instruction) {
  instruction = new_instruction;
  //  uint32_t opcode = getOpcode(instruction);
  /*  uint32_t operdan2;
  if (checkImmediate(instruction)) {
    operand2 = operandImmediate(instruction);
    }*/
}

int main(void) {
  uint32_t instruction = 0b00000010101101010101000000000000;
  data_processing(instruction);
  uint32_t s = checkSet();
  uint32_t i = checkImmediate();
  uint32_t opcode = getOpcode();
  uint32_t rn = getRn();
  uint32_t rd = getRd();
  
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

uint32_t getBits(uint32_t instruction, uint32_t mask, int shiftNo) {
  uint32_t bits = instruction & mask;
  return bits >> shiftNo;
}

uint32_t checkImmediate(void) {
  uint32_t mask = 0x2000000;
  return getBits(instruction, mask, 25);
}

uint32_t checkSet(void) {
  uint32_t mask = 0x100000;
  return getBits(instruction, mask, 20);
}

uint32_t getOpcode(void) {
  uint32_t mask = 0x1e00000;
  return getBits(instruction, mask, 21);
}

uint32_t getRn(void) {
  uint32_t mask = 0xf0000;
  return getBits(instruction, mask, 16);
}

uint32_t getRd(void) {
  uint32_t mask = 0xf000;
  return getBits(instruction, mask, 12);
}

uint32_t operandRotate(void) {
  uint32_t mask = 0xf00;
  return getBits(instruction, mask, 8);
}

uint32_t operandImmediate(void) {
  uint32_t mask = 0xff;
  return getBits(instruction, mask, 0);
}

uint32_t operandShift(void) {
  uint32_t mask = 0xff0;
  return getBits(instruction, mask, 4);
}

uint32_t operandRm(void) {
  uint32_t mask = 0xf;
  return getBits(instruction, mask, 0);
}
/*
uint32_t getOperand(void) {
  uint32_t operand;
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

void printBits(uint32_t x) {
  int i;
  uint32_t mask = 1 << 31;
  for(i=0; i<32; ++i) {
    if (i % 4 == 0)
      printf(" ");
    printf("%i", (x & mask) != 0);
    x <<= 1;
  }
  printf("\n ");
}
