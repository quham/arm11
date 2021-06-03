#include "ass_general.h"

void setPrePost(word32 instruction) {
  setBit(instruction, 24);
}

word32 singleDataTransfer(tokenset tokens) {
  word32 instruction = SDT_FORMAT;
  char *type = tokens.operands[0];
  char *rd = tokens.operands[1];
  char *addr = tokens.operands[2];
  char *post_expr = tokens.operands[3];
  setBits(&instruction, 12, regNumber(rd));  // set destination index

  if (!strcmp(type, "ldr")) {
    setBit(&instruction, 20);  // sets L bit
  }

  char *rn[REG_LEN] = addr;
  char *expr[WORD_SIZE] = post_expr;
  bool constant_address = addr[0] == '=';

  if (constant_address) {
    setPrePost(instruction);
    *rn = "r15";               // sets to PC
  } else if (!post_expr[0]) {  // pre-indexing
    setPrePost(instruction);
    *rn = strtok(addr, ",");
    char *offset = strtok(NULL, " ");
    if (offset != NULL) {  // zero offset
      *expr = *offset;
    }
  }

  word32 expr_value = strtol(*expr + 1, NULL, 0);

  if (constant_address) {
    if (expr_value <= MOV_CONSTANT_SIZE) {
      // reformat to mov
    } else {
      // store expr_value in four bytes
      // update expr_value with shifted
    }
  }

  setBits(&instruction, 0, expr_value);       // set offset
  setBits(&instruction, 16, regNumber(*rn));  // set base reg index

  return instruction;
}
