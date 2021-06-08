#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

word32 multiply(tokenset tokens) {
  word32 instruction = MUL_FORMAT;
  uint8_t regs[MUL_OPERANDS] = {0};

  if (!strcmp(tokens.opcode, "mla")) {
    setBits(&instruction, 11, regNumber(tokens.operands[ACC]));  // sets RN
    setBit(&instruction, 21);                                    // set accumulator
  }

  for (int i = 0; i < MUL_OPERANDS; i++) {
    regs[i] = regNumber(tokens.operands[i]);
  }

  setBits(&instruction, 15, regs[0]);  // set RD
  setBits(&instruction, 7, regs[2]);   // set RS
  setBits(&instruction, 0, regs[1]);   // set RM
  return instruction;
}
