#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t instr;
typedef uint8_t byte;
#define BYTES_PER_WORD 4
#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 17

struct State {
  word32 regs[NUMBER_OF_REGISTERS];
  byte memory[MEMORY_SIZE];
};

typedef struct State State;

// Reg Indices
#define PC_INDEX 15
#define CPSR_INDEX 16

// Pipeline
#define NOT_INIT 0xFFFFFFFF
#define BYTE_SIZE 8
#define PC_PIPELINE_OFFSET 8
typedef enum itype { PROCESSING, MULTIPLY, TRANSFER, BRANCH, TERMINATE } itype;
word32 fetch(word32 index, State*);
itype decode(instr);
void pipeline(State*);
void printRegisters(State*);
void printState(State*);

// Check condition
bool checkCond(instr, State* state);

// Data processing
#define ROTATION_MULTIPLIER 2
#define ROUNDING_ERROR 0.5
void dataProcessing(instr, State*);
void performOperation(void);
bool checkSub(word32, word32);
bool checkAdd(word32, word32);

// Single data transfer
void singleDataTransfer(instr, State*);
void store(word32, word32, State*);
word32 combineOffset(word32 reg, word32 offset, instr);
void transferData(State*, instr, word32 rd, word32 rdIndex, word32);

// Branch
void branch(instr, State*);

// Multiply
void multiply(instr, State*);

// Decomposition
#define ROTATION_MULTIPLIER 2
word32 getOperand(instr, bool is_immediate, State*);
word32 condCode(instr);
word32 getBits(word32, int start_index, int end_index);
word32 getRn(instr);
word32 getRd(instr);
word32 getRs(instr);
word32 getRm(instr);
bool addressValid(word32 addr);
bool checkBit(instr, int bit_no);
bool checkSet(instr);
bool checkImmediate(instr);
void setFlag(State*, int index, bool bit_value);
void rotateRight(word32* operand, int amount);
void makeShift(word32* operand, uint8_t shift_value, word32 shift_type, instr, State*, bool);
word32 signExtend(word32 number, int no_of_bits);

// Check condition
bool checkCond(instr, State*);

#endif  // EMULATOR_CONSTS
