#include "tokenizer.h"

tokenset tokenize(char line[]) {
  tokenset tokens  = {'\0', '\0', '\0'}; 
  char *opcode = line;
  if (strchr(line, ':')) {
    tokens.label   = strtok_r(opcode, ": ", &opcode);
  } else {
    char *operand  = opcode;
    tokens.opcode  = strtok_r(operand, " ", &operand);
    tokens.operand = operand;
  }
  return tokens;
}

void print_tokens(tokenset tokens) {
  printf("label: \"%s\", opcode: \"%s\", operand: \"%s\"\n",
   tokens.label, tokens.opcode, tokens.operand);
}

