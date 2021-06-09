#ifndef ARM_GENERAL_H
#define ARM_GENERAL_H

#include <stdint.h>

// binary types
typedef uint32_t word32;
typedef uint8_t byte;
typedef word32 instr;

#define WORD_SIZE 32
#define BYTE_SIZE 8

void setBit(word32 *, int index);

#endif  // ARM_CONSTS
