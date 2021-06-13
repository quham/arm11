#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

word32 singleDataTransfer(tokenset tokens, FILE *binary_file, word32 *binary_lines) {
  instr instruction = SDT_FORMAT;
  char *type = tokens.opcode;
  char *rd = tokens.operands[0];
  char *addr = tokens.operands[1];
  char *expr = tokens.operands[2];
  updateBits(&instruction, 12, regNumber(rd));  // set Rd bits

  if (!strcmp(type, "ldr")) {
    setBit(&instruction, 20);  // sets Load/Store flag
  }

  updateBaseReg(&instruction, regNumber(strtok(addr, "]")));  // TODO: assert safe

  if (addr[0] == '=') {  // check constant address
    setUpFlag(&instruction);
    setPrePostFlag(&instruction);
    word32 const_expr = readHex(addr + 1);
    if (const_expr < MOV_CONST) {
      char mov_expr[MOV_CONST_LEN + 2] = {'#', '\0'};
      safeStrCat(mov_expr, addr + 1);
      safeStrCpy(addr, mov_expr);
      safeStrCpy(type, "mov");
      return dataProcessing(tokens);
    } else {  // should gen new ldr instr?
      updateBaseReg(&instruction, PC_INDEX);
      word32 cur_addr = ftell(binary_file);              // TODO: assert safe
      word32 end_addr = *binary_lines * BYTES_PER_WORD;
      safeSeek(binary_file, end_addr);
      fwrite(&const_expr, sizeof(word32), 1, binary_file);  // TODO: unsafe
      (*binary_lines)++;
      safeSeek(binary_file, cur_addr);
      updateOffset(&instruction, relativeAddr(end_addr, cur_addr));
      return instruction;
    }
  }

  if (expr[0] == '\0') {  // check zero-offset
    setUpFlag(&instruction);
    setPrePostFlag(&instruction);
    return instruction;
  }

  if (expr[strlen(expr) - 1] == ']') {  // check pre-indexed
    setPrePostFlag(&instruction);
    expr[strlen(expr) - 1] = '\0';
  }

  if (expr[0] != '#') {  // check immediate
    setImmediate(&instruction);
  }

  expr++;                // remove leading '#' / 'r'
  if (expr[0] == '-') {  // check negative constants
    expr++;
  } else {
    setUpFlag(&instruction);
  }

  updateOffset(&instruction, readHex(expr));
  return instruction;
}

void setPrePostFlag(instr *instruction) {
  setBit(instruction, 24);
}

void setUpFlag(instr *instruction) {
  setBit(instruction, 23);
}

void updateBaseReg(instr *instruction, word32 value) {
  updateBits(instruction, 16, value);
}

void updateOffset(instr *instruction, word32 value) {
  updateBits(instruction, 0, value);
}
