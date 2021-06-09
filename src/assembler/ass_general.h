#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdio.h>
#include <stdbool.h>

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
#define SDT_FORMAT 0xe8000000;
#define MOV_CONSTANT_SIZE 0xff
#define REG_LEN 4

// Tokenizer
tokenset tokenize(char line[]);
void printTokens(tokenset);
tokenset checkLsl(tokenset);
extern char *strtok_r(char *, const char *, char **);

// Assemble
void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table, int lines);
Table symbolise(char asm_lines[][LINE_LENGTH]);

// Instruction compose
byte regNumber(char *reg_token);
void updateBits(word32 *, int index, word32 value);
void setCondCodeFlag(instr *);
void setImmediate(instr *);
void updateRm(instr *, byte rm);

// Data processing
#define DP_FORMAT 0xe0000000
word32 dataProcessing(tokenset tokens);
void setOperand(instr *, char operands[2][LINE_LENGTH]);
void setExpression(instr *, word32 expression);
byte getShiftTypeInt(const char *str);
byte getOpcode(word32 *instruction, const char *str, bool *computes_result);

// Multiply
#define MUL_FORMAT 0xe0000090
#define ACC 3
#define MUL_OPERANDS 3

#endif  // ASSEMBLER_CONSTS
