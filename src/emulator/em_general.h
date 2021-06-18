#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

#include <stdbool.h>
#include <stdint.h>

#include "arm_general.h"

#define MEMORY_SIZE 65536
#define MEMORY_WORD_SIZE 16384
#define NUMBER_OF_REGISTERS 17

typedef struct State {
  word32 regs[NUMBER_OF_REGISTERS];
  byte memory[MEMORY_SIZE];
} State;

// Pipeline
#define NOT_INIT 0xFFFFFFFF
typedef enum itype { PROCESSING, MULTIPLY, TRANSFER, BRANCH, TERMINATE } itype;
void pipeline(State*);
word32 fetch(word32 index, State*);
itype decode(instr);
void execute(itype, State*, word32* decoded, word32* fetched);
void printState(State*);

// Data processing
#define ROTATION_MULTIPLIER 2
#define ROUNDING_ERROR 0.5
enum opcode_bin { AND, EOR, SUB, RSB, ADD, TST = 8, TEQ = 9, CMP = 10, ORR = 12, MOV = 13 };
void dataProcessing(instr, State*);
bool checkAdd(word32 a, word32 b);
bool checkSub(word32 a, word32 b);

// Single data transfer
void singleDataTransfer(instr, State*);
word32 combineOffset(word32 reg, word32 offset, instr);
void transferData(State*, instr, word32 rd, word32 rdIndex, word32);
void store(word32, word32 addr, State*);

// Branch
void branch(instr, State*);

// Multiply
void multiply(instr, State*);

// Check condition
bool checkCond(instr, State*);

// Decomposition
#define ROTATION_MULTIPLIER 2
enum shift_type { LSL, LSR, ASR, ROR };
void updateFlag(State*, int index, bool bit_value);
bool checkBit(instr, int bit_no);
bool checkImmediate(instr);
bool checkSet(instr);
byte getByte(word32, int index);
byte condCode(instr);
byte getRs(instr);
byte getRm(instr);
byte getRd(instr);
byte getRn(instr);
word32 signExtend(word32 number, int no_of_bits);
bool validAddress(word32 addr);
word32 getOperand(instr, bool is_immediate, State*);
void rotateRight(word32* operand, int amount);
void decomp_tests(void);

#endif  // EMULATOR_CONSTS
