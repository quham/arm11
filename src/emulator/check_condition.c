#include "em_general.h"
#include <stdio.h>
#include <stdbool.h> 

// returns true if the condition code matches the CPSR flags.

bool checkCond(instr instruction, struct State *state) {

  word32 code   = condCode(instruction);
  word32 cpsr   = condCode(state->regs[CPSR_INDEX]);
  word32 n_flag = getBit(cpsr, 31); //n is position 3 of cond
  word32 z_flag = getBit(cpsr, 30); //z is position 2 of cond
  word32 v_flag = getBit(cpsr, 28); //v is position 0 of cond

// each hex val is a possible cond code: succeeds if cpsr flags match.
  bool eq = (code == 0x0)  && z_flag;   
  bool ne = (code == 0x1)  && !z_flag;
  bool ge = (code == 0x10) && (n_flag == v_flag);
  bool lt = (code == 0x11) && (n_flag != v_flag);
  bool gt = (code == 0x12) && !z_flag && (n_flag == v_flag);
  bool le = (code == 0x13) && (z_flag || (n_flag != v_flag));
  bool la = (code == 0x14); 

  return eq || ne || ge || lt || gt || le || la;
}
