#include <stdbool.h>
#include <stdio.h>

#include "em_general.h"

// returns true if the condition code matches the CPSR flags
bool checkCond(instr instruction, State *state) {
  word32 code = condCode(instruction);
  word32 cpsr = state->regs[CPSR_INDEX];
  bool n_flag = checkBit(cpsr, 31);
  bool z_flag = checkBit(cpsr, 30);
  bool v_flag = checkBit(cpsr, 28);

  // check each code and respective cpsr flags
  bool eq = (code == 0x0) && z_flag;
  bool ne = (code == 0x1) && !z_flag;
  bool ge = (code == 0xa) && (n_flag == v_flag);
  bool lt = (code == 0xb) && (n_flag != v_flag);
  bool gt = (code == 0xc) && !z_flag && (n_flag == v_flag);
  bool le = (code == 0xd) && (z_flag || (n_flag != v_flag));
  bool al = (code == 0xe);

  return eq || ne || ge || lt || gt || le || al;
}
