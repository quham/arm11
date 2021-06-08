#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

void setPrePost(word32 instruction) {
  setBit(&instruction, 24);
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

  char rn[REG_LEN];
  strcpy(rn, addr);
  char expr[WORD_SIZE];
  strcpy(expr, post_expr);
  bool constant_address = addr[0] == '=';

  if (constant_address) {
    setPrePost(instruction);
    strcpy(rn, "r15");      // sets to PC
  } else if (!post_expr) {  // pre-indexing
    setPrePost(instruction);
    strcpy(rn, strtok(addr, ","));  // sets to PC
    char *offset = strtok(NULL, " ");
    if (!offset) {           // zero offset
      strcpy(expr, "#0x0");  // sets to PC
    }
  }

  word32 expr_value = strtol(expr + 1, NULL, 0);

  if (constant_address) {
    if (expr_value <= MOV_CONSTANT_SIZE) {
      // reformat to mov
    } else {
      // store expr_value in four bytes
      // update expr_value with shifted
    }
  }

  setBits(&instruction, 0, expr_value);       // set offset
  setBits(&instruction, 16, regNumber(rn));  // set base reg index

  return instruction;
}
