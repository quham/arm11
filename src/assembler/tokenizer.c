#include "tokenizer.h"

tokenset tokenize(char line[]) {
  tokenset tokens  = {'\0', '\0', '\0'}; 
  char *instruction = line;
  if (strchr(line, ':')) {
    tokens.label   = strtok_r(instruction, ": ", &instruction);
  } else {
    tokens.opcode  = strtok_r(instruction, " ", &instruction);
    tokens.operand = instruction;
  }
  return tokens;
}

void print_tokens(tokenset tokens) {
  printf("label: \"%s\", opcode: \"%s\", operand: \"%s\"\n",
   tokens.label, tokens.opcode, tokens.operand);
}

