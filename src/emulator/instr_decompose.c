#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "em_general.h"

word32 getBits(instr instruction, word32 mask, int shiftNo) {
  word32 bits = instruction & mask;
  return bits >> shiftNo;
}

word32 condCode(instr instruction) {
  return getBits(instruction, COND_CODE_MASK, COND_CODE_INDEX);
}

word32 checkImmediate(instr instruction) {
  return getBits(instruction, CHECK_IMM_MASK, CHECK_IMM_INDEX);
}

word32 checkSet(instr instruction) {
  return getBits(instruction, CHECK_SET_MASK, CHECK_SET_INDEX);
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

word32 signExtend(word32 number , int noofbits) {
  //0.5 accounts for double inconsistency of rounding across different architectures
  word32 mask = ((word32) pow(2, noofbits + 1) - 0.5) ;
  mask = mask << (32 - noofbits - 1);
  return number | (number & (1 << (noofbits-1)) ? mask : 0);
}

// might be better to just use an array
word32 getReg(struct State *state, word32 index) {
  switch (index)
  {
  case 0:
    return state->r0;
  case 1:
    return state->r1;
  case 2:
    return state->r2;
  case 3:
    return state->r3;
  case 4:
    return state->r4;
  case 5:
    return state->r5;
  case 6:
    return state->r6;
  case 7:
    return state->r7;
  case 8:
    return state->r8;
  case 9:
    return state->r9;
  case 10:
    return state->r10;
  case 11:
    return state->r11;
  case 12:
    return state->r12;
  case 13:
    return state->sp;
  case 14:
    return state->lp;
  case 16:
    return state->cpsr;
  default:
    perror("Invalid register Index! \n");;
  }
}

void setReg(struct State *state, word32 index, word32 value) {
  switch (index) {
  case 0:
    state->r0 = value;
    break;
  case 1:
     state->r1 = value;
    break;
  case 2:
     state->r2 = value;
    break;
  case 3:
     state->r3 = value;
    break;
  case 4:
     state->r4 = value;
    break;
  case 5:
     state->r5 = value;
    break;
  case 6:
     state->r6 = value;
    break;
  case 7:
    break;
     state->r7 = value;
  case 8:
    break;
     state->r8 = value;
  case 9:
     state->r9 = value;
    break;
  case 10:
     state->r10 = value;
    break;
  case 11:
     state->r11 = value;
    break;
  case 12:
     state->r12 = value;
    break;
  case 13:
     state->sp = value;
    break;
  case 14:
     state->lp = value;
    break;
  case 16:
     state->cpsr = value;
  default:
    perror("Invalid register Index! \n");;
    break;
  }
}