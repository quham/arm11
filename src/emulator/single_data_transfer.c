#include <stdint.h>
#include "em_general.h"

word32 checkLoadStore(instr instruction, struct State *state) {
  return getBits(instruction, LOAD_STORE_MASK, LOAD_STORE_INDEX);
}

word32 checkUp(instr instruction) {
  return getBits(instruction, CHECK_UP_MASK, CHECK_UP_INDEX);
}

word32 checkPrePost(instr instruction) {
  return getBits(instruction, CHECK_PRE_POST_MASK, CHECK_PRE_POST_INDEX);
}

word32 getRnSDT(instr instruction, struct State *state) {
  return getReg(state, getBits(instruction, SDT_RN_MASK, SDT_RN_INDEX));
}

word32 getRdSDT(instr instruction, struct State *state) {
  return getReg(state, getBits(instruction, SDT_RD_MASK, SDT_RD_INDEX));
}

void single_data_transfer(instr instruction, struct State *state) {
  
}