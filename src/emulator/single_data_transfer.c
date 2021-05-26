#include <stdint.h>

#include "em_general.h"

void single_data_transfer(instr instr, State *state) {
  word32 offset = getOperand(instr);
  // ^ not correct (reverse of data proc)
  word32 rdIndex = getRd(instr);
  word32 rnIndex = getRn(instr);
  word32 rd = state->regs[rdIndex];
  word32 rn = state->regs[rnIndex];
  word32 addr = combine_offset(rn, offset, instr);
  if (checkBit(instr, 24)) {
    transfer_data(state, instr, rd, rdIndex, addr);
  } else {
    transfer_data(state, instr, rd, rdIndex, rn);
    state->regs[rnIndex] = addr;
  }
}

word32 combine_offset(word32 reg, word32 offset, instr instr) {
  if (checkBit(instr, 23)) {
    return reg + offset;
  } else {
    return reg - offset;
  }
}

void transfer_data(State *state, instr instr, word32 rd, word32 rdIndex, word32 addr) {
  if (checkBit(instr, 20)) {
    state->regs[rdIndex] = state->memory[addr];
  } else {
    state->memory[addr] = rd;
  }
}

// make instruction global?