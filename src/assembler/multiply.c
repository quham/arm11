#include "ass_general.h"
#include "tokenizer.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000
#define MUL_OP_NUM 3

int getRegNum(char reg[]);

/* shift values, for position in instruction */
#define RD_POS 0xf
#define RN_POS 0xb
#define RS_POS 0x7

word32 multiply(tokenset tokens) {
  word32 instruction = MUL_FORMAT;
  uint8_t regs[MAX_OPERANDS] = {0};

  for (int i = 0; i < MUL_OP_NUM; i++) {
      regs[i] = getRegNum(tokens.operands[i]);
  }

  if (!strcmp(tokens.opcode, "mla")) {
    uint8_t rn = getRegNum(tokens.operands[MUL_OP_NUM]);
    instruction |= rn << RN_POS | A_BIT;
  }

  /* rd, rs and rm placed into instruction */
  instruction |= (regs[0] << RD_POS) | (regs[2] << RS_POS) | regs[1];
  return instruction;
}

int getRegNum(char reg[]) {
    char *end;
    return (int) strtol(reg, &end, 10);
}