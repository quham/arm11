#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

void removeWhitespace(char **str) {
  if (*str[0] == ' ' || *str[0] == '[') {
    (*str)++;
  }
}

tokenset tokenize(char *line) {
  tokenset tokens = {"\0", {{"\0"}}};
  strcpy(tokens.opcode, strtok_r(line, " ", &line));
  // TODO: Safe str copying / assertions
  char *reg = strtok(line, ",");

  for (int op = 0; reg; op++) {
    assert(op < MAX_OPERANDS);
    removeWhitespace(&reg);
    strcat(tokens.operands[op], reg);
    reg = strtok(NULL, ",");
  }
  return checkLsl(tokens);
}

void printTokens(tokenset tokens) {
  printf("%s\n", "__tokens__ ");
  printf("opcode: \"%s\"\n", tokens.opcode);
  for (int i = 0; i < MAX_OPERANDS; i++) {
    printf("operand %d: %s\n", i, tokens.operands[i]);
  }
}

tokenset checkLsl(tokenset tokens) {
  if (strcmp(tokens.opcode, "lsl")) {
    return tokens;
  }
  if (strchr(tokens.operands[1], '#')) {
    printf("%s\n", "replacing lsl");
    // TODO: Safe str copying / assertions
    strcpy(tokens.opcode, "mov");
    strcpy(tokens.operands[2], "lsl ");
    strcat(tokens.operands[2], tokens.operands[1]);
    strcpy(tokens.operands[1], tokens.operands[0]);
  }
  return tokens;
}
