#include <stdint.h>

#include "em_general.h"

word32 checkLoadStore(instr instr) { return getBit(instr, LOAD_STORE_INDEX); }

word32 checkUp(instr instr) { return getBit(instr, CHECK_UP_INDEX); }

word32 checkPrePost(instr instr) { return getBit(instr, CHECK_PRE_POST_INDEX); }

void single_data_transfer(instr instr, struct State *state) {
  word32 offset = getOperand(instr);
  // ^ not correct (reverse of data proc)
  word32 rdIndex = getRd(instr);
  word32 rnIndex = getRn(instr);
  word32 rd = state->regs[rdIndex];
  word32 rn = state->regs[rnIndex];
  word32 addr = combine_offset(rn, offset, instr);
  if (checkPrePost(instr)) {
    transfer_data(state, instr, rd, rdIndex, addr);
  } else {
    transfer_data(state, instr, rd, rdIndex, rn);
    state->regs[rnIndex] = addr;
  }
}

word32 combine_offset(word32 reg, word32 offset, instr instr) {
  if (checkUp(instr)) {
    return reg + offset;
  } else {
    return reg - offset;
  }
}

void transfer_data(struct State *state, instr instr, word32 rd, word32 rdIndex,
                   word32 addr) {
  if (checkLoadStore(instr)) {
    state->regs[rdIndex] = state->memory[addr];
  } else {
    state->memory[addr] = rd;
  }
}

// todo: make instr global to be uniform with data_processing
// implement check cond
// compute offset correctly
// correct style (snake case etc)