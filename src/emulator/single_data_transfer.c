#include <stdlib.h>

#include "em_general.h"

void singleDataTransfer(instr instruction, State *state) {
  word32 offset = getOperand(instruction, !checkImmediate(instruction), state);
  byte rd_index = getRd(instruction);
  byte rn_index = getRn(instruction);
  word32 rd = state->regs[rd_index];
  word32 rn = state->regs[rn_index];
  word32 addr = combineOffset(rn, offset, instruction);

  if (checkBit(instruction, 24)) {  // check pre/post bit
    transferData(state, instruction, rd, rd_index, addr);
  } else {
    transferData(state, instruction, rd, rd_index, rn);
    state->regs[rn_index] = addr;
  }
}

word32 combineOffset(word32 reg, word32 offset, instr instruction) {
  if (checkBit(instruction, 23)) {  // check up bit
    return reg + offset;
  } else {
    return reg - offset;
  }
}

void transferData(State *state, instr instruction, word32 rd, word32 rd_index, word32 addr) {
  if (checkBit(instruction, 20)) {  // check load/store bit
    state->regs[rd_index] = fetch(addr, state);
  } else {
    store(rd, addr, state);
  }
}

// stores little endian byte ordered word in big-endian format
void store(word32 word, word32 addr, State *state) {
  if (validAddress(addr)) {
    for (int i = 0; i < BYTES_PER_WORD; i++) {
      state->memory[addr + i] = getByte(word, i);
    }
  }
}
