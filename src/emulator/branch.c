#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void branch(instr instruction, State *state) {
  word32 offset = getBits(instruction, 0, 24) << 2;
  // offset bits multiplied by 4 (shifted by 2) since words are aligned on 4 bytes
  offset = signExtend(offset, 26);  // sign extend 26-bit offset
  state->regs[PC_INDEX] += offset;
}
