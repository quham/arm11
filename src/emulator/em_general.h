#include <stdbool.h>

#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

typedef uint32_t instr;
typedef uint32_t word32;
#define WORD_SIZE 32
#define MEMORY_SIZE 65536
#define ADDRESS_SIZE 2
#define INSTR_SIZE 4
#define NUMBER_OF_REGISTERS 17

struct State {
  word32 regs[NUMBER_OF_REGISTERS];
  word32 memory[MEMORY_SIZE];
};

typedef struct State State;

// Reg Indexs
#define R0_INDEX 0
#define R1_INDEX 1
#define R2_INDEX 2
#define R3_INDEX 3
#define R4_INDEX 4
#define R5_INDEX 5
#define R6_INDEX 6
#define R7_INDEX 7
#define R8_INDEX 8
#define R9_INDEX 9
#define R10_INDEX 10
#define R11_INDEX 11
#define R12_INDEX 12
#define SP_INDEX 13
#define LP_INDEX 14
#define PC_INDEX 15
#define CPSR_INDEX 16

// Pipeline
void pipeline(State*);
typedef enum itype { PROCESSING, MULTIPLY, TRANSFER, BRANCH, TERMINATE } itype;
itype decode(instr);
#define NOT_INIT 0xFFFFFFFF

// Data processing
void performOperation(void);
void data_processing(instr, State*);
void printBits(instr);
word32 getOpcode(void);
word32 operandRotate(void);
word32 operandImmediate(void);
word32 oprandShift(void);
word32 operandRm(void);
int checkSub(word32 a, word32 b);
int checkAdd(word32 a, word32 b);

#define ROUNDING_ERROR 0.5

// Single data transfer
void single_data_transfer(instr, State*);

// Branch
void branch(instr, State*);

// Multiply
void multiply(instr, State*);

// Decomposition
#define ROTATION_MULTIPLIER 2
word32 getOperand(instr, bool is_immediate, State*);
word32 condCode(instr);
word32 getBits(instr, int start_index, int end_index);
word32 getRn(instr);
word32 getRd(instr);
word32 getRs(instr);
word32 getRm(instr);
void setFlag(State *state, int index, bool bit_value);
bool checkBit(instr, int bit_no);
bool checkSet(instr);
bool checkImmediate(instr);
void rotateRight(word32* operand, int amount);
void makeShift(word32* operand, word32 shift_value, word32 shift_type, instr, State*);
word32 getOperandRefactor(instr, bool cond, State*);
word32 signExtend(word32 number, int no_of_bits);

// Check condition
bool checkCond(instr, State*);

#endif  // EMULATOR_CONSTS
