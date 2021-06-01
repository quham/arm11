#ifndef ASS_TOKENIZER_H
#define ASS_TOKENIZER_H
#include <string.h>
#include <stdio.h>


typedef union tokens {
  char *label;
  struct ops { 
    char *opcode;
    char *operands[4];
  } ops;
} tokens;

tokens tokenize(char line[]);
void print_tokens(tokenset);


#endif
