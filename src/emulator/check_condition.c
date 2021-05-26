#include <stdbool.h>
#include <stdio.h>

#include "em_general.h"

// returns true if the condition code matches the CPSR flags

bool checkCond(instr instruction, State *state) {
  word32 code = condCode(instruction);
  word32 cpsr = condCode(state->regs[CPSR_INDEX]);
  word32 n_flag = checkBit(cpsr, 31);
  word32 z_flag = checkBit(cpsr, 30);
  word32 v_flag = checkBit(cpsr, 28);

  // check each code and respective cpsr flags
  bool eq = (code == 0b0000) && z_flag;
  bool ne = (code == 0b0001) && !z_flag;
  bool ge = (code == 0b1010) && (n_flag == v_flag);
  bool lt = (code == 0b1011) && (n_flag != v_flag);
  bool gt = (code == 0b1100) && !z_flag && (n_flag == v_flag);
  bool le = (code == 0b1101) && (z_flag || (n_flag != v_flag));
  bool al = (code == 0b1110);

  return eq || ne || ge || lt || gt || le || al;
}
