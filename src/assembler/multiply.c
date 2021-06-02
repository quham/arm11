#include "ass_general.h"
#include "tokenizer.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000
#define REG_NUM 1

/* shift values, for position in instruction */
#define RD_POS 0xf
#define RN_POS 0xb
#define RS_POS 0x7

word32 multiply(tokenset tokens) {
  word32 instruction = MUL_FORMAT;
  uint8_t rd = tokens.operands[0][1];
  uint8_t rm = tokens.operands[1][1];
  uint8_t rs = tokens.operands[2][1];

  if (!strcmp(tokens.opcode, "mla")) {
    instruction |= A_BIT;
    uint8_t rn = tokens.operands[3][1];
    instruction |= rn << RN_POS;
  }

  instruction |= rm;
  instruction |= rd << RD_POS;
  instruction |= rs << RS_POS;
  return instruction;
}
