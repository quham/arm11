#ifndef ARM_GENERAL_H
#define ARM_GENERAL_H

#include <stdint.h>
#include <stdio.h>

#define BYTES_PER_WORD 4

// Reg Indices
#define PC_INDEX 15
#define CPSR_INDEX 16

// binary types
typedef uint32_t word32;
typedef uint8_t byte;
typedef word32 instr;

#define WORD_SIZE 32
#define BYTE_SIZE 8

void setBit(word32*, int index);
word32 getBits(word32, int start_index, int end_index);
void safeStrCpy(char* dest, char* src, int n);
void safeSeek(FILE*, word32 file_len);

#endif  // ARM_CONSTS
