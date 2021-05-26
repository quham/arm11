#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

typedef uint32_t instr;
typedef uint32_t word32;
#define WORD_SIZE 32
#define MEMORY_SIZE 65536
#define ADDRESS_SIZE 2
#define INSTR_SIZE 4
#define NUMBER_OF_REGISTERS 17
#define PC 15
#define CPSR 16

struct State {
  word32 regs[NUMBER_OF_REGISTERS];
  word32 memory[MEMORY_SIZE];
};

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

//Pipeline
#define NOT_INIT 0xFFFFFFFF

// Data processing
void data_processing(instr, struct State*);
void printBits(instr);
word32 getOpcode(void);
#define OPCODE_MASK 0x1e00000
#define OPCODE_INDEX 21
word32 operandRotate(void);
#define OPERAND_ROTATE_MASK 0xf00
#define OPERAND_ROTATE_INDEX 8
word32 operandImmediate(void);
#define OPERAND_IMM_MASK 0xff
#define OPERAND_IMM_INDEX 0
word32 oprandShift(void);
#define OPERAND_SHIFT_MASK 0xff0
#define OPERAND_SHIFT_INDEX 4
word32 operandRm(void);
#define OPERAND_RM_MASK 0xf
#define OPERAND_RM_INDEX 0
word32 getRn(instr);
#define OPERAND_RN_MASK 0xf0000
#define OPERAND_RN_INDEX 16
word32 getRd(instr);
#define OPERAND_RD_MASK 0xf000
#define OPERAND_RD_INDEX 12
word32 getRs(instr);
#define RS_MASK 0xf00
#define RS_INDEX 8
word32 getRm(instr);
#define RM_MASK 0xf
#define RM_INDEX 0

#define ROUNDING_ERROR 0.5

// Single data transfer
void single_data_transfer(instr, struct State*);
#define LOAD_STORE_INDEX 20
#define CHECK_UP_INDEX 23
#define CHECK_PRE_POST_INDEX 24
#define SDT_RN_MASK 0xf0000
#define SDT_RN_INDEX 16
#define SDT_RD_MASK 0xf000
#define SDT_RD_INDEX 12

// Branch
void branch(instr, struct State*);

// Multiply
void multiply(instr, struct State*);

// Decomposition
word32 signExtend(word32 number, int noofbits);
word32 getBits(instr, word32 mask, int shiftNo);
word32 getBit(instr instruction, int bitNo);
void makeShift(word32* instruction, word32 shift_value, word32 shift_type);
void rotateRight(word32* operand, int amount);
word32 condCode(instr);
#define COND_CODE_INDEX 28
word32 checkImmediate(instr);
#define CHECK_IMM_INDEX 25
word32 checkSet(instr);
#define CHECK_SET_INDEX 20

#endif  // EMULATOR_CONSTS
