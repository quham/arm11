#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "em_general.h"

uint32_t signExtend(u_int32_t number , int noofbits){
    uint32_t mask = ((uint32_t) pow( 2, noofbits + 1) - 0.5) ;//0.5 accounts for double inconsistency of rounding across different architectures
    mask = mask << (32 - noofbits - 1);
    return number | (number & (1 << (noofbits-1)) ? mask : 0);
}

void branch(instr instruction, struct State *state){
    u_int32_t cpsrMask = 0xF0000000;
    u_int32_t offsetMask = 0x00FFFFFF;
    u_int32_t flags = getBits(instruction, cpsrMask , 0);
    if (flags == state->cpsr){
        u_int32_t offset = getBits(instruction , offsetMask, 0) << 2;
        offset = signExtend(offset, 26);
        // offset = offset | ((offset & (1<<25)) ? 0xFC000000 : 0); //specific case of sign extend
        state->pc += offset - 8;
}