#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

word32 dataProcessing(tokenset tokens) {
  if (!strncmp(tokens.opcode, "andeq", 5)) {
    return 0;
  }
  bool computes_result = true;
  byte rd, rn;
  rd = rn = 0;
  instr instruction = DP_FORMAT;

  byte opcode = getOpcode(&instruction, tokens.opcode, &computes_result);
  if (computes_result) {
    rd = regNumber(tokens.operands[0]);
    rn = regNumber(tokens.operands[1]);
    // passing last 2 arguments
    setOperand(&instruction, &tokens.operands[2]);
  } else {
    // passing last 2 arguments
    setOperand(&instruction, &tokens.operands[1]);
    if (!strncmp(tokens.opcode, "mov", DATA_PROC_OPCODE_LEN)) {
      rd = regNumber(tokens.operands[0]);
    } else {
      rn = regNumber(tokens.operands[0]);
    }
  }
  updateBits(&instruction, 12, rd);
  updateBits(&instruction, 16, rn);
  updateBits(&instruction, 21, opcode);
  return instruction;
}

// function takes just last two operands
void setOperand(instr *instruction, char operands[2][LINE_LENGTH]) {
  if (operands[0][0] == '#') {
    //  gets immediate from any base
    word32 imm = strtol(operands[0] + 1, NULL, 0);
    setExpression(instruction, imm);
  } else {
    byte rm = regNumber(operands[0]);
    if (operands[1][0] != '\0') {  // when there is a shift
      char *shift_type = strtok(operands[1], " ");
      char *shift_operand = strtok(NULL, " ");

      word32 shift_op;
      word32 shift_t = getShiftTypeInt(shift_type);

      // this if-else sets shift operand
      if (shift_operand[0] == '#') {
        shift_op = strtol(shift_operand + 1, NULL, 0);
        if (shift_op > FIVE_BIT_INTEGER) {
          perror("Error: Shift-operand value is too big\n");
          exit(EXIT_FAILURE);
        }
      } else {
        setBit(instruction, 4);  // set for register shift
        shift_op = regNumber(shift_operand);
        shift_op <<= 1;  // 7s bit is 0 for register shift
      }

      updateBits(instruction, 5, shift_t);   // set shift type
      updateBits(instruction, 7, shift_op);  // set shift op
    }
    updateRm(instruction, rm);
  }
}

// Encodes a numeric constant.
// If number < 256, then can be directly encoded.
// If number > 256, then checking whether rotated
// number can be encoded. If 1 is on LSB and number
// greater than 1, it can`t fit in 8 bits -> error.
void setExpression(instr *instruction, word32 expression) {
  setImmediate(instruction);
  byte rotation = 0;

  if (expression < 256) {
    updateBits(instruction, 0, expression);
  } else {
    while (!(expression & 1)) {  // shifts and compares LSB with 1
      expression >>= 1;
      rotation++;
    }
    if (rotation % 2 != 0) {
      expression <<= 1;
      rotation--;
    }
    if (expression < 256) {
      // should complete the rotation, also accounts
      // for rotation multiplier in emulator
      rotation = (WORD_SIZE - rotation) / ROTATION_MULTIPLIER;
      updateBits(instruction, 0, expression);
      updateBits(instruction, 8, rotation);
    } else {
      // rotation cannot be made
      perror("Error: Immediate value does not fit in 8 bits\n");
      exit(EXIT_FAILURE);
    }
  }
}

// TODO: write symbol table
byte getShiftTypeInt(char *str) {
  if (!strncmp(str, "lsl", DATA_PROC_OPCODE_LEN))
    return 0;
  if (!strncmp(str, "lsr", DATA_PROC_OPCODE_LEN))
    return 1;
  if (!strncmp(str, "asr", DATA_PROC_OPCODE_LEN))
    return 2;
  if (!strncmp(str, "ror", DATA_PROC_OPCODE_LEN))
    return 3;
  perror("Error: Unsupported shift type\n");
  exit(EXIT_FAILURE);
}

// Returns opcode. Sets S Flag if needed.
// computes_result shows if 2 or 3 arguments
byte getOpcode(word32 *instruction, char *str, bool *computes_result) {
  if (!strncmp(str, "and", DATA_PROC_OPCODE_LEN))
    return 0x0;
  if (!strncmp(str, "eor", DATA_PROC_OPCODE_LEN))
    return 0x1;
  if (!strncmp(str, "sub", DATA_PROC_OPCODE_LEN))
    return 0x2;
  if (!strncmp(str, "rsb", DATA_PROC_OPCODE_LEN))
    return 0x3;
  if (!strncmp(str, "add", DATA_PROC_OPCODE_LEN))
    return 0x4;
  if (!strncmp(str, "tst", DATA_PROC_OPCODE_LEN)) {
    *computes_result = false;
    setCondCodeFlag(instruction);
    return 0x8;
  }
  if (!strncmp(str, "teq", DATA_PROC_OPCODE_LEN)) {
    *computes_result = false;
    setCondCodeFlag(instruction);
    return 0x9;
  }
  if (!strncmp(str, "cmp", DATA_PROC_OPCODE_LEN)) {
    *computes_result = false;
    setCondCodeFlag(instruction);
    return 0xa;
  }
  if (!strncmp(str, "orr", DATA_PROC_OPCODE_LEN))
    return 0xc;
  if (!strncmp(str, "mov", DATA_PROC_OPCODE_LEN)) {
    *computes_result = false;
    return 0xd;
  }
  perror("Error: Unsupported opcode\n");
  exit(EXIT_FAILURE);
}
