#ifndef ASS_TOKENIZER_H
#define ASS_TOKENIZER_H
#include <string.h>
#include <stdio.h>

typedef struct tokens {

  char *label;
  char *opcode;
  char *operand;

} tokenset;

tokenset tokenize(char line[]);
void print_tokens(tokenset);


#endif
