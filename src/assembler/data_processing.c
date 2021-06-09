#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

// const char* compute_results = {"and", "eor", "sub", "rsb", "add", "orr"};
// const char* not_compute_results = {"tst", "teq", "cmp"};

void printBits(word32 x) {
  int i;
  word32 mask = 1 << 31;
  for (i = 0; i < 32; ++i) {
    if (i % 4 == 0)
      printf(" ");
    if ((x & mask) == 0) {
      printf("0");
    } else {
      printf("1");
    }
    x = x << 1;
  }
  printf("\n ");
}

// int main(void) {
//   char *str = "sub r1, r2, r3, lsl r4";
//   printf("1\n");
//   tokenset tokens = tokenize(str);
//   //word32 instruction = dataProcessing(&tokens);
//   //printBits(instruction);
//   printf("0\n");
//   return 0;
// }

word32 dataProcessing(tokenset *tokens) {
  instr instruction = DP_FORMAT;
  byte opcode = getOpcode(&instruction, tokens->opcode);
  setOperand(&instruction, tokens->operands + 2 * LINE_LENGTH);
  updateBits(&instruction, 20, opcode);
  // mov is checked first so we can distinguish between add, tst, etc
  // instructions and set condition code flag (S flag) if needed

  return instruction;
}

// function takes just third and fourth agruments
void setOperand(instr *instruction, char operands[2][LINE_LENGTH]) {
  byte rm = regNumber(operands[0]);
  if (operands[0][0] == '#') {
    setExpression(instruction, rm);
  } else {
    if (operands[1] != NULL) {  // whether there is a shift
      char **save_ptr = NULL;
      char *shift_type, *shift_operand;
      shift_type = strtok_r(operands[1], " ", save_ptr);
      shift_operand = strtok_r(NULL, " ", save_ptr);
      word32 shift_op;
      word32 shift_t = getShiftTypeInt(shift_type);

      // this if-else sets shift operand
      if (shift_operand[0] == '#') {
        shift_op = strtol(shift_operand + 1, NULL, 0);
        if (shift_op >= 64) { // magic number
          perror("Error: Shift-operand value is too big\n");
          exit(EXIT_FAILURE);
        }
      } else {
        setBit(instruction, 4);  // set for register shift
        shift_op = atoi(shift_operand + 1);
        shift_op <<= 1;  // so takes 5 bits as immediate
      }

      updateBits(instruction, 5, shift_t);   // set shift type
      updateBits(instruction, 7, shift_op);  // set shift op
    }
    updateRm(instruction, rm);
  }
  return;
}

// Encodes a numeric constant.
// If number is less then 256, then we can surely encode it,
// otherwise we might need to rotate until we find a one on LSB
// and compare to 256 again, but also include rotation bits or
// print an error.
void setExpression(instr *instruction, word32 expression) {
  setImmediate(instruction);

  word32 rotation = 0;
  if (expression < 256) {
    updateBits(instruction, 0, expression);
  }

  while (!(expression & 1)) {  // shifts and compares LSB with 1
    expression >>= 1;
    rotation++;
  }
  if (expression < 256) {
    rotation = WORD_SIZE - rotation;  // full rotation should be made, so leftovers are encoded
    updateBits(instruction, 0, expression);  // set Immediate expression
    updateBits(instruction, 8, rotation);    // set rotate bits
  } else {
    perror("Error: Immediate value does not fit in 8 bits\n");
    exit(EXIT_FAILURE);
  }
}

// TODO: use else if to short circuit evaluation?
byte getShiftTypeInt(const char *str) {
  if (!strcmp(str, "lsl"))
    return 0;
  if (!strcmp(str, "lsr"))
    return 1;
  if (!strcmp(str, "asr"))
    return 2;
  if (!strcmp(str, "ror"))
    return 3;
  perror("Error: Unsupported shift type\n");
  exit(EXIT_FAILURE);
}

// TODO: use else if to short circuit evaluation?
byte getOpcode(word32 *instruction, const char *str) {
  if (!strcmp(str, "and"))
    return 0;
  if (!strcmp(str, "eor"))
    return 1;
  if (!strcmp(str, "sub"))
    return 2;
  if (!strcmp(str, "rsb"))
    return 3;
  if (!strcmp(str, "add"))
    return 4;
  if (!strcmp(str, "tst")) {
    setCondCodeFlag(instruction);
    return 8;
  }
  if (!strcmp(str, "teq")) {
    setCondCodeFlag(instruction);
    return 9;
  }
  if (!strcmp(str, "cmp")) {
    return 10;
  }
  if (!strcmp(str, "orr"))
    return 12;
  if (!strcmp(str, "mov"))
    return 13;
  perror("Error: Unsupported opcode\n");
  exit(EXIT_FAILURE);
}
