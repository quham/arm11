#include <stdbool.h>

#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

typedef uint32_t instr;
typedef uint32_t word32;
typedef uint16_t address;
typedef uint8_t byte;
#define WORD_SIZE 32
#define BYTES_PER_WORD 4
#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 17

struct State {
  word32 regs[NUMBER_OF_REGISTERS];
  byte memory[MEMORY_SIZE];
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
typedef enum itype { PROCESSING, MULTIPLY, TRANSFER, BRANCH, TERMINATE } itype;
void pipeline(State*);
word32 fetch(address index, State*);
itype decode(instr);
void execute(instr, enum itype type, State*, word32* decoded, word32* fetched);
void printRegisters(State*);
#define NOT_INIT 0xFFFFFFFF
#define BYTE_SIZE 8

// Data processing
#define ROTATION_MULTIPLIER 2
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
void store(word32, address, State*);
word32 combine_offset(word32 reg, word32 offset, instr);
void transfer_data(State*, instr, word32 rd, word32 rdIndex, address);

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
void setFlag(State*, int index, bool bit_value);
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
