#include <stdint.h>
#include "em_general.h"

word32 checkLoadStore(instr instruction, struct State *state) {
  word32 mask = 0x100000;
  return getBits(instruction, mask, 20);
}

word32 checkUp(instr instruction) {
  word32 mask = 0x800000;
  return getBits(instruction, mask, 23);
}

word32 checkPrePost(instr instruction) {
  word32 mask = 0x1000000;
  return getBits(instruction, mask, 24);
}

void single_data_transfer(instr instruction, struct State *state)
{
}
