#include <stdbool.h>
#include <stdio.h>

#include "em_general.h"

void dataProcessing(instr instruction, State *state) {
  word32 result;
  word32 operand2 = getOperand(instruction, checkImmediate(instruction), state);
  word32 rn = state->regs[getRn(instruction)];
  word32 *rd = &state->regs[getRd(instruction)];
  byte opcode = getBits(instruction, 21, 25);
  bool carry_out = checkBit(state->regs[CPSR_INDEX], 31);

  switch (opcode) {
    case AND:
      result = rn & operand2;
      *rd = result;
      break;
    case EOR:
      result = rn ^ operand2;
      *rd = result;
      break;
      case SUB:
      result = rn - operand2;
      *rd = result;
      carry_out = checkSub(rn, operand2);
      break;
    case RSB:
      result = operand2 - rn;
      *rd = result;
      carry_out = checkSub(operand2, rn);
      break;
    case ADD:
      result = rn + operand2;
      *rd = result;
      carry_out = checkAdd(rn, operand2);
      break;
    case TST:
      result = rn & operand2;
      break;
    case TEQ:
      result = rn ^ operand2;
      break;
    case CMP:
      result = rn - operand2;
      carry_out = checkSub(rn, operand2);
      break;
    case ORR:
      result = rn | operand2;
      *rd = result;
      break;
    case MOV:
      result = operand2;
      *rd = result;
      break;
    default:
      perror("Error: Unsupported ALU operation\n");
      break;
  }

  if (checkSet(instruction)) {
    bool z_flag = result == 0;
    bool n_flag = checkBit(result, 31);
    updateFlag(state, 31, n_flag);
    updateFlag(state, 30, z_flag);
    updateFlag(state, 29, carry_out);
  }
}

bool checkAdd(word32 a, word32 b) {
  return a > (UINT32_MAX - b);
}

bool checkSub(word32 a, word32 b) {
  return a >= b;
}
