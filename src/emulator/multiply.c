#include <stdint.h>

#include "check_condition.c"
#include "data_processing.c"
#include "em_general.h"
#include "instr_decompose.c"

void multiply(instr instruction, State *state) {
  if (!checkCond(instruction, state)) {
    return;
  }

  word32 acc = checkBit(instruction, 21);
  word32 rd = getBits(instruction, 20, 16); 
  word32 rn = getBits(instruction, 16, 12); 
  word32 rm = getBits(instruction, 4, 0);   
  word32 rs = getBits(instruction, 12, 8); 
  word32 *regs = state->regs;

  if (acc) {
    regs[rd] = regs[rm] * regs[rs] + regs[rn];
  } else {
    regs[rd] = regs[rm] * regs[rs];
  }

  if (checkSet(instruction)) {
    regs[CPSR_INDEX] = regs[CPSR_INDEX] | 0x100000000;  // sets Nflag to 1
    if (!(regs[rd])) {
      regs[CPSR_INDEX] = regs[CPSR_INDEX] | 0x80000000;  // sets Zflag to 1 if rd is 0
    }
  }
}
