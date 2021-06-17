#include <stdlib.h>

#include "ass_general.h"

instr branch(tokenset tokens, word32 pc, Table* sym_table) {
  instr instruction = BRANCH_FORMAT;

  word32 target;
  if (tokens.operands[0][0] == '#') {
    target = readHex(tokens.operands[0] + 1);
  } else {
    target = lookup(sym_table, tokens.operands[0]);
  }

  updateBits(&instruction, 0, getBits(relativeAddr(target, pc), 2, 26));

  word32 cond;
  // change to symbol table
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
      break;
  }
  updateBits(&instruction, 28, cond);

  return instruction;
}
