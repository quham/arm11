#ifndef ASS_TOKENIZER_H
#define ASS_TOKENIZER_H
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_OPERANDS 4

typedef struct tokens {
  char *opcode;
  char *operands[MAX_OPERANDS];
} tokenset;

tokenset tokenize(char line[]);
void printTokens(tokenset);

#endif
