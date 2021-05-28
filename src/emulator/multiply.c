#include <stdint.h>

#include "em_general.h"

void multiply(instr instruction, State *state) {
  word32 acc = checkBit(instruction, 21);
  word32 rd = getBits(instruction, 16, 20);
  word32 rn = getBits(instruction, 12, 16);
  word32 rm = getBits(instruction, 0, 4);
  word32 rs = getBits(instruction, 8, 12);
  word32 *regs = state->regs;

  if (acc) {
    regs[rd] = regs[rm] * regs[rs] + regs[rn];
  } else {
    regs[rd] = regs[rm] * regs[rs];
  }

  if (checkSet(instruction)) {
    setFlag(state, 28, 1);  // set overflow
    if (!(regs[rd])) {
      setFlag(state, 31, 1);  // set negative
    }
  }
}
