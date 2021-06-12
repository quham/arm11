#ifndef ASS_GENERAL_H
#define ASS_GENERAL_H

#include <stdbool.h>
#include <stdio.h>

#include "../arm_general.h"

#define MAX_OPERANDS 4
#define MAX_OPCODE_LEN 5
#define LINE_LENGTH 511

typedef struct tokens {
  char opcode[MAX_OPCODE_LEN];
  char operands[MAX_OPERANDS][LINE_LENGTH];
} tokenset;

// Symbol Table
#define INITIAL_MAX_TABLE_SIZE 4  // maybe a little big
typedef struct Pair Pair;
typedef struct Table Table;

struct Pair {
  char *key;
  word32 value;
};

struct Table {
  int *size;
  int *max_size;
  Pair *elements;
};

Table *makeTable();
void put(Table *, Pair pair);
word32 lookup(Table *, char *str);
void freeTable(Table *);

// Single data transfer
#define SDT_FORMAT 0xe4000000;
#define MOV_CONST 0xff
#define MOV_CONST_LEN 4
#define REG_LEN 4
word32 singleDataTransfer(tokenset, FILE *file, word32 *lines);
void setPrePostFlag(instr *);
void setUpFlag(instr *);
void updateBaseReg(instr *, word32 value);

// Tokenizer
tokenset tokenize(char line[]);
void printTokens(tokenset);
tokenset checkLsl(tokenset);
extern char *strtok_r(char *, const char *, char **);

// Assemble
#define LINE_LENGTH 511
void assemble(FILE *assembly_file, FILE *binary_file, Table *sym_table, word32 num_of_lines);

// Instruction compose
byte regNumber(char *reg_token);
word32 readHex(char *hex);
void updateBits(word32 *, int index, word32 value);
void setCondCodeFlag(instr *);
void setImmediate(instr *);
void updateRm(instr *, byte rm);

// Data processing
#define DP_FORMAT 0xe0000000
word32 dataProcessing(tokenset);
void setOperand(instr *, char operands[2][LINE_LENGTH]);
void setExpression(instr *, word32 expression);
byte getShiftTypeInt(const char *str);
byte getOpcode(word32 *instruction, const char *str, bool *computes_result);

// Multiply
#define MUL_FORMAT 0xe0000090
#define ACC 3
#define MUL_OPERANDS 3
word32 multiply(tokenset);

// Branch
instr branch(tokenset, word32 address, Table *);

#endif  // ASSEMBLER_CONSTS
