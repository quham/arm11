#include "em_general.h"

void multiply(instr instruction, State *state) {
  bool acc = checkBit(instruction, 21);
  byte rd = getBits(instruction, 16, 20);
  byte rn = getBits(instruction, 12, 16);
  byte rm = getBits(instruction, 0, 4);
  byte rs = getBits(instruction, 8, 12);
  word32 *regs = state->regs;

  regs[rd] = regs[rm] * regs[rs];

  if (acc) {
    regs[rd] += regs[rn];
  }

  if (checkSet(instruction)) {
    updateFlag(state, 28, 1);  // set overflow
    if (!(regs[rd])) {
      updateFlag(state, 31, 1);  // set negative
    }
  }
}
