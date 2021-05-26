#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

void branch(instr instruction, State *state) {
  if (checkCond(instruction, state)) {
    word32 offset = getBits(instruction, 0, 23) << 2;
    offset = signExtend(offset, 26);
    // offset = offset | ((offset & (1<<25)) ? 0xFC000000 : 0); // specific case of signExtend
    state->regs[PC_INDEX] += offset - 8;
  }
}
