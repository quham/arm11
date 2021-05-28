#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_general.h"

instr instruction = 0;
State *state;

void data_processing(instr new_instruction, State *new_state) {
  instruction = new_instruction;
  state = new_state;
  performOperation();
}

void performOperation(void) {
  int32_t result;
  word32 opcode = getBits(instruction, 21, 25);
  word32 operand2 = getOperand(instruction, checkImmediate(instruction), state);
  int32_t rn = state->regs[getRn(instruction)];
  int32_t *rd = state->regs + getRd(instruction);
  bool carry_out = checkBit(state->regs[CPSR_INDEX], 31);

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
      carry_out = checkSub(rn, operand2);
      break;
    case 3:  // 0011 rsb
      result = operand2 - rn;
      *rd = result;
      carry_out = checkSub(operand2, rn);
      break;
    case 4:  // 0100 add
      result = rn + operand2;
      *rd = result;
      carry_out = checkAdd(rn, operand2);
      break;
    case 8:  // 1000 tst
      result = rn & operand2;
      break;
    case 9:  // 1001 teq
      result = rn ^ operand2;
      break;
    case 10:  // 1010 cmp
      result = rn - operand2;
      carry_out = checkSub(rn, operand2);
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

  if (checkSet(instruction)) {
    bool Z = result == 0;
    bool N = checkBit(result, 31);
    setFlag(state, 31, N);
    setFlag(state, 30, Z);
    setFlag(state, 29, carry_out);
  }
}

bool checkAdd(word32 a, word32 b) {
  return (a > UINT32_MAX - b);
}

bool checkSub(word32 a, word32 b) {
  return a < b;
}
