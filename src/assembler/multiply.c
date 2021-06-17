#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

word32 multiply(tokenset tokens) {
  word32 instruction = MUL_FORMAT;
  byte regs[MUL_OPERANDS] = {0};

  if (!strcmp(tokens.opcode, "mla")) { // TODO: assert safe?
    updateBits(&instruction, 12, regNumber(tokens.operands[ACC]));  // sets Rn
    setBit(&instruction, 21); // set accumulator
  }

  for (int i = 0; i < MUL_OPERANDS; i++) {
    regs[i] = regNumber(tokens.operands[i]);
  }

  updateBits(&instruction, 16, regs[0]);  // set Rd
  updateBits(&instruction, 8, regs[2]);   // set Rs
  updateRm(&instruction, regs[1]);
  return instruction;
}
