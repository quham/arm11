#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPERANDS 4
#define MAX_OPCODE_LEN 5
#define LINE_LENGTH 511

typedef struct tokens {
  char opcode[MAX_OPCODE_LEN];
  char operands[MAX_OPERANDS][LINE_LENGTH];
} tokenset;

// Single data transfer
#define SDT_FORMAT 0xe8000000;
#define REG_LEN 3

// Tokenizer
tokenset tokenize(char line[]);
void printTokens(tokenset);

// Assembler
struct Table {
  char *test;
};

typedef struct Table Table;
Table symbolise(char asm_lines[][LINE_LENGTH]);
void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table);

#endif  // ASSEMBLER_CONSTS
