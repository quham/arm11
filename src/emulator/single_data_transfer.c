#include <stdint.h>

#include "em_general.h"

word32 checkLoadStore(instr instruction) {
  return getBits(instruction, LOAD_STORE_MASK, LOAD_STORE_INDEX);
}

word32 checkUp(instr instruction) {
  return getBits(instruction, CHECK_UP_MASK, CHECK_UP_INDEX);
}

word32 checkPrePost(instr instruction) {
  return getBits(instruction, CHECK_PRE_POST_MASK, CHECK_PRE_POST_INDEX);
}

void single_data_transfer(instr instruction, struct State *state) {
  word32 offset = getOperand(instruction);
  // ^ not correct (reverse of data proc)
  word32 rdIndex = getRd(instruction);
  word32 rnIndex = getRn(instruction);
  word32 rd = getReg(state, rdIndex);
  word32 rn = getReg(state, rnIndex);
  word32 addr = combine_offset(rn, offset, instruction);
  if (checkPrePost(instruction)) {
    transfer_data(state, instruction, rd, rdIndex, addr);
  } else {
    transfer_data(state, instruction, rd, rdIndex, rn);
    setReg(state, rnIndex, addr);
  }
}

word32 combine_offset(word32 reg, word32 offset, instr instruction) {
  if (checkUp(instruction)) {
    return reg + offset;
  } else {
    return reg - offset;
  }
}

// no memory access
void transfer_data(struct State *state, instr instruction, word32 rd,
                   word32 rdIndex, word32 addr) {
  if (checkLoadStore(instruction)) {
    setReg(state, rdIndex, memory[addr])
  } else {
    memory[addr] = rd;
  }
}

// todo: make instruction global to be uniform with data_processing
// Make memory access correct
// implement check cond
// compute offset correctly
// correct style (snake case etc)