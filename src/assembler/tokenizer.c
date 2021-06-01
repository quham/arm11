#include "tokenizer.h"

#define MAX_OPERANDS 4

tokenset tokenize(char line[]) {
  tokenset tokens = {NULL};
  char *instruction = line;
  if (!strchr(line, ':')) {
    tokens.opcode  = strtok_r(instruction, " ", &instruction);
    char *reg = strtok(instruction, ",");
    int i = 0;
    while (reg != NULL) {
        tokens.operands[i] = reg;
        reg = strtok(NULL, ",");
        i++;
    }
  }
  return tokens;
}

void print_tokens(tokenset tokens) {
  printf("%s\n", "tokens: ");
  printf("opcode: \"%s\"\n", tokens.opcode);
  for (int i = 0; i < MAX_OPERANDS; i++) {
    printf("operand %d: %s\n", i, tokens.operands[i]);
  }



}

