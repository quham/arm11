#include <stdlib.h>

#include "ass_general.h"

instr branch(tokenset tokens, word32 address, Table *sym_table) {
  word32 target = 0;
  if (tokens.operands[0][0] == '#') {
    target = strtol(tokens.operands[0] + 1, NULL, 0);
  } else {
    target = lookup(sym_table, tokens.operands[0]);
  }
  word32 offset = getBits(target - address - 8, 26, 2);  // address of curr instr
  instr binary = offset;
  updateBits(&binary, 24, 0xa);  // branch format
  word32 cond;
  switch (tokens.opcode[1]) {
    case 'e':
      cond = 0x0;
      break;
    case 'n':
      cond = 0x1;
      break;
    case 'g':
      if (tokens.opcode[2] == 'e') {
        cond = 0xa;
      } else {
        cond = 0xc;
      }
      break;
    case 'l':
      if (tokens.opcode[2] == 'e') {
        cond = 0xd;
      } else {
        cond = 0xb;
      }
      break;
    default:
      cond = 0xe;
  }
  updateBits(&binary, 28, cond);
  return binary;
}
