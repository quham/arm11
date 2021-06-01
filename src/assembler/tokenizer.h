#ifndef ASS_TOKENIZER_H
#define ASS_TOKENIZER_H
#include <string.h>
#include <stdio.h>

typedef struct ops ops;
typedef union tokens {
  char *label;
  ops { 
    char *opcode;
    char *operands[4];
  };
} tokenset;

tokenset tokenize(char line[]);
void print_tokens(tokenset);


#endif
