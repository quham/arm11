#include <stdint.h>
#include <stdio.h>

#include "em_general.h"

void store(word32 word, address addr, State *state) {
  for (int i = 0; i < BYTES_PER_WORD; i++) {
    state->memory[addr + i] = getBits(word, i * BYTE_SIZE, (i + 1) * BYTE_SIZE);
  }
}

word32 combine_offset(word32 reg, word32 offset, instr instruction) {
  if (checkBit(instruction, 23)) {  // check up bit
    return reg + offset;
  } else {
    return reg - offset;
  }
}

void transfer_data(State *state, instr instruction, word32 rd, word32 rdIndex, address addr) {
  if (checkBit(instruction, 20)) {  // check load/store bit
    state->regs[rdIndex] = fetch(addr, state);
  } else {
    store(rd, addr, state);
  }
}

void single_data_transfer(instr instruction, State *state) {
  word32 offset = 0;
  getOperand(instruction, !checkImmediate(instruction), state);
  word32 rdIndex = getRd(instruction);
  word32 rnIndex = getRn(instruction);
  word32 rd = state->regs[rdIndex];
  word32 rn = state->regs[rnIndex];
  address addr = combine_offset(rn, offset, instruction);

  if (checkBit(instruction, 24)) {  // check pre/post bit
    transfer_data(state, instruction, rd, rdIndex, addr);
  } else {
    transfer_data(state, instruction, rd, rdIndex, rn);
    state->regs[rnIndex] = addr;
  }
}
