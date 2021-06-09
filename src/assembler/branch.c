#include "ass_general.h"

instr branch(tokenset tokens, word32 address, Table table) {
  word32 target = 0;
  if (isalpha(tokens.operands[0][0])) {  // is alpha not digits
    // target = lookup(table, tokens.operands[0]);
  } else {
    target = atoi(tokens.operands[0]);
  }
  word32 offset = getBits(target - address - 8, 26, 2);  // address of curr instr
  instr binary = offset;
  setBits(&binary, 24, 0xa);  // branch format
  word32 cond = 0;
  switch (tokens.opcode[0][1]) {
    case 'e':
      cond = 0x0;
      break;
    case 'n':
      cond = 0x1;
      break;
    case 'g':
      if (tokens.opcode[0][2] == 'e') {
        cond = 0xa;
      } else {
        cond = 0xc;
      }
      break;
    case 'l':
      if (tokens.opcode[0][2] == 'e') {
        cond = 0xd;
      } else {
        cond = 0xb;
      }
      break;
    default:
      cond = 0xe;
  }
  setBits(&binary, 28, cond);
  return binary;
}
