#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

tokenset tokenize(char *line) {
  tokenset tokens = {"\0", {{"\0"}}};
  safeStrCpy(tokens.opcode, strtok(line, " "));  // TODO: assert safe strtok

  char *reg = strtok(NULL, ",");
  for (int op = 0; reg; op++) {
    assert(op < MAX_OPERANDS);
    removeWhitespace(&reg);
    safeStrCat(tokens.operands[op], reg);
    reg = strtok(NULL, ",");
  }
  return checkLsl(tokens);
}

void removeWhitespace(char **str) {
  if (*str[0] == ' ') {
    (*str)++;
  }
  if (*str[0] != '\0') {
    if (*str[0] == '[') {
      (*str)++;
    }
  }
}

void printTokens(tokenset tokens) {
  printf("%s\n", "__tokens__ ");
  printf("opcode: \"%s\"\n", tokens.opcode);
  for (int i = 0; i < MAX_OPERANDS; i++) {
    printf("operand %d: %s\n", i, tokens.operands[i]);
  }
}

tokenset checkLsl(tokenset tokens) {
  if (strncmp(tokens.opcode, "lsl", DATA_PROC_OPCODE_LEN)) {
    return tokens;
  }
  if (strchr(tokens.operands[1], '#')) {
    printf("%s\n", "replacing lsl");
    // TODO: Safe str copying / assertions
    safeStrCpy(tokens.opcode, "mov");
    safeStrCpy(tokens.operands[2], "lsl ");
    safeStrCat(tokens.operands[2], tokens.operands[1]);
    safeStrCpy(tokens.operands[1], tokens.operands[0]);
  }
  return tokens;
}
