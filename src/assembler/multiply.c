#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000
#define ACC 3
#define MUL_OPERANDS 3

uint8_t getRegNum(char reg[]);

/* shift values, for position in instruction */
#define RD_POS 0xf
#define RN_POS 0xb
#define RS_POS 0x7

word32 multiply(tokenset tokens) {
  word32 instruction = MUL_FORMAT;
  uint8_t regs[MUL_OPERANDS] = {0};

  if (!strcmp(tokens.opcode, "mla")) {
    instruction |= (getRegNum(tokens.operands[ACC]) << RN_POS) | A_BIT;
  }

  for (int i = 0; i < MUL_OPERANDS; i++) {
    regs[i] = getRegNum(tokens.operands[i]);
  }

  /* rd, rs and rm placed into instruction */
  instruction |= (regs[0] << RD_POS) | (regs[2] << RS_POS) | regs[1];
  return instruction;
}

uint8_t getRegNum(char reg[]) {
  return strtol(reg + 1, NULL, 10);
}
