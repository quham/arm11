#ifndef EMULATOR_CONSTS
#define EMULATOR_CONSTS

#include <stdio.h>

typedef uint32_t instr;
#define MEMORY_SIZE 65536
#define ADDRESS_SIZE 2
#define INSTR_SIZE 4
#define NUMBER_OF_REGISTERS 17
#define PC 15
#define CPSR 16

struct State
{
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
  uint32_t r12;
  uint32_t sp;
  uint32_t lp;
  uint32_t pc;
  uint32_t cpsr;
};

#endif //EMULATOR_CONSTS
