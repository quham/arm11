#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t word32;
#define MAX_OPERANDS 4

typedef struct tokens {
  char *opcode;
  char operands[MAX_OPERANDS];
} tokenset;

#endif
