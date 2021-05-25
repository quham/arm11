#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

#include <stdio.h>

typedef uint32_t instr;
typedef uint32_t word32;
#define MEMORY_SIZE 65536
#define ADDRESS_SIZE 2
#define INSTR_SIZE 4
#define NUMBER_OF_REGISTERS 17
#define PC 15
#define CPSR 16

struct State
{
  word32 r0;
  word32 r1;
  word32 r2;
  word32 r3;
  word32 r4;
  word32 r5;
  word32 r6;
  word32 r7;
  word32 r8;
  word32 r9;
  word32 r10;
  word32 r11;
  word32 r12;
  word32 sp;
  word32 lp;
  word32 pc;
  word32 cpsr;
};

// data processing
void data_processing(instr, struct State*);
void printBits(instr);
word32 getRn(instr);
word32 getRd(instr);
word32 getOpcode(void);
word32 operandRotate(void);
word32 operandImmediate(void);
word32 oprandShift(void);
word32 operandRm(void);

// Single data transfer
void single_data_transfer(instr, struct State*);

// Branch
void branch(instr, struct State*);

// Multiply
void multiply(instr, struct State*);

// decomposition
word32 getBits(instr, word32 mask, int shiftNo);
word32 condCode(instr);
word32 checkImmediate(instr);
word32 checkSet(instr);
void rotateRight(word32* operand, int amount);

#endif //EMULATOR_CONSTS
