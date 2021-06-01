#include <stdint.h>
#include <stdio.h>

#include "em_general.h"

// stores little endian byte ordered word in big-endian format
void store(word32 word, word32 addr, State *state) {
  if (addressValid(addr)) {
    for (int i = 0; i < BYTES_PER_WORD; i++) {
      state->memory[addr + i] = getBits(word, i * BYTE_SIZE, (i + 1) * BYTE_SIZE);
    }
  }
}

word32 combine_offset(word32 reg, word32 offset, instr instruction) {
  if (checkBit(instruction, 23)) {  // check up bit
    return reg + offset;
  } else {
    return reg - offset;
  }
}

void transfer_data(State *state, instr instruction, word32 rd, word32 rd_index, word32 addr) {
  if (checkBit(instruction, 20)) {  // check load/store bit
    state->regs[rd_index] = fetch(addr, state);
  } else {
    store(rd, addr, state);
  }
}

void single_data_transfer(instr instruction, State *state) {
  word32 offset = getOperand(instruction, !checkImmediate(instruction), state);
  word32 rd_index = getRd(instruction);
  word32 rn_index = getRn(instruction);
  word32 rd = state->regs[rd_index];
  word32 rn = state->regs[rn_index];
  word32 addr = combine_offset(rn, offset, instruction);

  if (checkBit(instruction, 24)) {  // check pre/post bit
    transfer_data(state, instruction, rd, rd_index, addr);
  } else {
    transfer_data(state, instruction, rd, rd_index, rn);
    state->regs[rn_index] = addr;
  }
}
