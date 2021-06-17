#include "em_general.h"

void branch(instr instruction, State *state) {
  // offset bits multiplied by 4 (shifted by 2) since words are aligned on 4 bytes
  word32 offset = getBits(instruction, 0, 24) << 2;
  // sign extend 26-bit offset
  offset = signExtend(offset, 26);
  state->regs[PC_INDEX] += offset;
}
