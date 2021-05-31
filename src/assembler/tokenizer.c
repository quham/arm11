#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

tokenset tokenize(char line[]) {
  tokenset tokens = {'\0', '\0', '\0'}; 
  char *label;
  char *opcode = line;
  if (strchr(line, ':')) {
    label          = strtok_r(opcode, ": ", &opcode);
    tokens.label   = label;
  } else {
    char *operand  = opcode;
    opcode         = strtok_r(operand, " ", &operand);
    tokens.opcode  = opcode;
    tokens.operand = operand;
  }
  return tokens;
}

void print_tokens(tokenset tokens) {
  printf("label: \"%s\", opcode: \"%s\", operand: \"%s\"\n",
   tokens.label, tokens.opcode, tokens.operand);
}

