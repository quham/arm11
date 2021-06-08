#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

tokenset tokenize(char line[]) {
  tokenset tokens = {"\0", {{"\0"}}};

  if (line[0] != '\0') {
    char *instruction = line;
    strcpy(tokens.opcode, sstrtok_r(instruction, " ", &instruction));

    char *reg = strtok(instruction, ",");
    int op = 0;
    while (reg != NULL) {
      char *has_closing = strchr(reg, ']');
      while (reg[0] == ' ') {
        reg++;
      }

      if (reg[0] == '[' && !has_closing) {  // at least 2 elements in bracket
        reg++;
        strcat(tokens.operands[op], reg);
        strcat(tokens.operands[op], ",");
        reg = strtok(NULL, "]");
      }

      if (reg[0] == '[' && has_closing) {  // just 1 element in bracket
        memcpy(tokens.operands[op], reg + 1, 2);
      } else {
        strcat(tokens.operands[op], reg);
      }

      reg = strtok(NULL, ",");
      op++;
    }
  }
  return checkLsl(tokens);
  ;
}

char *removeWhitespace(char *str) {
  while (isspace(*str)) {
    str++;
  }
  return str;
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
    strcpy(tokens.opcode, "mov");
    strcpy(tokens.operands[2], "lsl ");
    strcat(tokens.operands[2], tokens.operands[1]);
    strcpy(tokens.operands[1], tokens.operands[0]);
  }
  return tokens;
}
