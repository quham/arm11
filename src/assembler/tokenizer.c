#include "tokenizer.h"



tokens tokenize(char line[]) {
  tokens tokens;
  char *instruction = line;
  if (strchr(line, ':')) {
    tokens.label    = strtok_r(instruction, ": ", &instruction);
  } else {
    tokens.ops.opcode  = strtok_r(instruction, " ", &instruction);

    char *reg = strtok(instruction, ",");
    int i = 0;
    while (reg != NULL) {
        tokens.ops.operands[i] = reg;
        reg = strtok(NULL, ",");
        i++;
    }
  }

  return tokens;
}

void print_tokens(tokens tokens) {
  printf("label: \"%s\", opcode: \"%s\", operand: \"%s\"\n",
   tokens.label, tokens.ops.opcode, tokens.ops.operands[0]);
}

