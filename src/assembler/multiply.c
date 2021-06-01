#include "ass_general.h"
#include "tokenizer.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000


word32 multiply(tokenset tokens) {
    word32 instruction = MUL_FORMAT;


    if (!strcmp(tokens.opcode, "mla")) {
        instruction |= A_BIT;
    } else {
    }

    return instruction;
} 




