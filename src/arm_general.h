#ifndef ARM_GENERAL_H
#define ARM_GENERAL_H

#include <stdint.h>

typedef uint32_t word32;
typedef uint8_t byte;
typedef word32 instr;
#define WORD_SIZE 32

void setBit(word32 *word, int index);

#endif  // ARM_CONSTS
