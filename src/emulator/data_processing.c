#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

#define ROTATION_MULTIPLIER 2  // define in em_general.h

instr instruction = 0;
State *state;

void data_processing(word32 new_instruction, State *new_state) {
  instruction = new_instruction;
  state = new_state;
}

// int main(void) {
//   return 0;
// }

void performOperation(void) {
  word32 result;
  word32 opcode = getBits(instruction, 21, 24);
  word32 operand2 = getOperand(instruction, checkImmediate(instruction), state);
  word32 rn = state->regs[getBits(instruction, 15, 19)];  // can we use getRn here?
  word32 *rd = state->regs + getBits(instruction, 16, 19);
  //  word32 carry_out = checkBit(state->regs[CPSR_INDEX], 31);

  switch (opcode) {
    case 0:  // 0000 and
      result = rn & operand2;
      *rd = result;
      break;
    case 1:  // 0001 eor
      result = rn ^ operand2;
      *rd = result;
      break;
    case 2:  // 0010 sub
      result = rn - operand2;
      *rd = result;
      break;
    case 3:  // 0011 rsb
      result = operand2 - rn;
      *rd = result;
      break;
    case 4:  // 0100 add
      result = rn + operand2;
      *rd = result;
      break;
    case 8:  // 1000 tst
      result = rn & operand2;
      break;
    case 9:  // 1001 teq
      result = rn ^ operand2;
      break;
    case 10:  // 1010 cmp
      result = rn - operand2;
      break;
    case 12:  // 1100 orr
      result = rn | operand2;
      *rd = result;
      break;
    case 13:  // 1101 mov
      result = operand2;
      *rd = result;
      break;
  }

  /*
  if (checkSet(instruction)) {
    char Z = (result == 0) ? 1 : 0;
    char N = checkBit(result, 31);
    check for overflow here (or in the add related cases)

    May look up conditions in comp arch;
  */
  return;
}
