#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

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

// Single data transfer
void single_data_transfer(instr, struct State*);
#define LOAD_STORE_MASK 0x100000
#define LOAD_STORE_INDEX 20
#define CHECK_UP_MASK 0x800000
#define CHECK_UP_INDEX 23
#define CHECK_PRE_POST_MASK 0x1000000
#define CHECK_PRE_POST_INDEX 24

// Branch
void branch(instr, struct State*);

// Multiply
void multiply(instr, struct State*);

// decomposition
word32 signExtend(word32 number , int noofbits);
word32 getBits(instr, word32 mask, int shiftNo);
word32 getSpecificBit(instr instruction, int bitNo);
void makeShift(word32* instruction, word32 shift_value, word32 shift_type);
void rotateRight(word32* operand, int amount);
word32 condCode(instr);
#define COND_CODE_MASK 0xF0000000
#define COND_CODE_INDEX 28
word32 checkImmediate(instr);
#define CHECK_IMM_MASK 0x2000000
#define CHECK_IMM_INDEX 25
word32 checkSet(instr);
#define CHECK_SET_MASK 0x100000
#define CHECK_SET_INDEX 20

#endif //EMULATOR_CONSTS
