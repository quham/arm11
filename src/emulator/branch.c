#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "em_general.h"


void branch(instr instruction, struct State *state){
    word32 cpsrMask = 0xF0000000;
    word32 offsetMask = 0x00FFFFFF;
    word32 flags = getBits(instruction, cpsrMask , 0);
    if (flags == state->cpsr){
        word32 offset = getBits(instruction , offsetMask, 0) << 2;
        offset = signExtend(offset, 26);
        // offset = offset | ((offset & (1<<25)) ? 0xFC000000 : 0); //specific case of sign extend
        state->pc += offset - 8;
}
