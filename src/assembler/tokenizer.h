#ifndef ASS_TOKENIZER_H
#define ASS_TOKENIZER_H
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

tokenset tokenize(char line[]);
void printTokens(tokenset);

#endif
