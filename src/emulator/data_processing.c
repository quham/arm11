#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

uint32_t checkBit(uint32_t, int);
void data_processing(uint32_t);
uint32_t checkImmediate(uint32_t);
uint32_t checkSet(uint32_t);
uint32_t getOpcode(uint32_t);
uint32_t getRn(uint32_t);
uint32_t getRd(uint32_t);
uint32_t getBits(uint32_t, uint32_t, int);
void printBits(uint32_t);

void data_processing(uint32_t instruction) {
 uint32_t s = checkSet(instruction);
 uint32_t i = checkImmediate(instruction);
 uint32_t opcode = getOpcode(instruction);
 uint32_t rn = getRn(instruction);
 uint32_t rd = getRd(instruction);

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
 
}

int main(void) {
  uint32_t x = 0b00000010101101010101000000000000;
  data_processing(x);
 
  return 0;
}

//Returns specific bits of the instruction. Mask selects the
//ending and shiftNo the beginning of the required bits.
uint32_t getBits(uint32_t instruction, uint32_t mask, int shiftNo) {
  uint32_t bits = instruction & mask;
  return bits >> shiftNo;
}

uint32_t checkImmediate(uint32_t instruction) {
  uint32_t mask = 0x2000000;
  return getBits(instruction, mask, 25);
}

uint32_t checkSet(uint32_t instruction) {
  uint32_t mask = 0x100000;
  return getBits(instruction, mask, 20);
}

uint32_t getOpcode(uint32_t instruction) {
  uint32_t mask = 0x1e00000;
  return getBits(instruction, mask, 21);
}

uint32_t getRn(uint32_t instruction) {
  uint32_t mask = 0xf0000;
  return getBits(instruction, mask, 16);
}

uint32_t getRd(uint32_t instruction) {
  uint32_t mask = 0xf000;
  return getBits(instruction, mask, 12);
}

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
