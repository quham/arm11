#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdbool.h>
#include <stdio.h>

#include "arm_general.h"

#define MAX_OPERANDS 4
#define MAX_OPCODE_LEN 6
#define LINE_LENGTH 511
#define PC_PIPELINE_OFFSET 8

typedef struct tokens {
  char opcode[MAX_OPCODE_LEN];
  char operands[MAX_OPERANDS][LINE_LENGTH];
} tokenset;

// Symbol Table
#define INITIAL_MAX_TABLE_SIZE 4

typedef struct Pair {
  char *key;
  word32 value;
} Pair;

typedef struct Table {
  size_t *size;
  int *max_size;
  Pair *elements;
} Table;

Table *makeTable(void);
void put(Table *, char *key, word32 value);
word32 lookup(Table *, char *str);
void freeTable(Table *);

// Single data transfer
#define SDT_FORMAT 0xe4000000;
#define SDT_OPCODE_LEN 3
#define MOV_CONST 0xff
#define MOV_CONST_LEN 4
#define REG_LEN 4
word32 singleDataTransfer(tokenset, FILE *file, word32 *lines);
void setPrePostFlag(instr *);
void setUpFlag(instr *);
void updateBaseReg(instr *, word32 value);
void updateOffset(instr *, word32 value);

// Tokenizer
tokenset tokenize(char line[]);
void printTokens(tokenset);
tokenset checkLsl(tokenset);
extern char *strtok_r(char *, char *, char **);
void removeWhitespace(char **);

// Assemble
void assemble(FILE *assembly_file, FILE *binary_file, Table *sym_table, word32 num_of_lines);

// Instruction compose
byte regNumber(char *reg_token);
word32 readHex(char *hex);
void updateBits(word32 *, int index, word32 value);
void setCondCodeFlag(instr *);
void setImmediate(instr *);
void updateRm(instr *, byte rm);
word32 relativeAddr(word32 target, word32 pc);

// Data processing
#define DP_FORMAT 0xe0000000
#define DATA_PROC_OPCODE_LEN 3
#define FIVE_BIT_INTEGER 31
#define HALF_WORD 16
#define ROTATION_MULTIPLIER 2
word32 dataProcessing(tokenset);
void setOperand(instr *, char operands[2][LINE_LENGTH]);
void setExpression(instr *, word32 expression);
byte getShiftTypeInt(char *str);
byte getOpcode(word32 *instruction, char *str, bool *computes_result);

// Multiply
#define MUL_FORMAT 0xe0000090
#define MULT_OPCODE_LEN 3
#define ACC 3
#define MUL_OPERANDS 3
word32 multiply(tokenset);

// Branch
#define BRANCH_FORMAT 0x0a000000
instr branch(tokenset, word32 pc, Table *);

#endif  // ASSEMBLER_CONSTS
