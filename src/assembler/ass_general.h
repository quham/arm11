#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdio.h>

#include "../arm_general.h"

#define MAX_OPERANDS 4
#define MAX_OPCODE_LEN 5
#define LINE_LENGTH 511

typedef struct tokens {
  char opcode[MAX_OPCODE_LEN];
  char operands[MAX_OPERANDS][LINE_LENGTH];
} tokenset;

struct Table {
  char *test;
};
typedef struct Table Table;

// Single data transfer
#define MOV_CONSTANT_SIZE 0xff
#define SDT_FORMAT 0xe8000000;
#define REG_LEN 4

// Tokenizer
tokenset tokenize(char line[]);
void printTokens(tokenset);
tokenset checkLsl(tokenset);
char *removeWhitespace(char *str);

// Assemble
void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table, int lines);
Table symbolise(char asm_lines[][LINE_LENGTH]);

// Instruction compose
uint8_t regNumber(char *reg_token);
void setBits(word32 *word, int index, word32 value);

// Multiply
#define MUL_FORMAT 0xe0000090
#define ACC 3
#define MUL_OPERANDS 3

#endif  // ASSEMBLER_CONSTS
