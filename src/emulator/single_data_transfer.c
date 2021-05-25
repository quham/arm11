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

void single_data_transfer(instr instruction, struct State *state)
{
}
