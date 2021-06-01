#include "ass_general.h"
#include "tokenizer.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000
#define REG_NUM 1

/* shift values, for position in instruction */
#define RD_POS 0xf
#define RN_POS 0xb
#define RS_POS 0x7


word32 multiply(tokenset tokens) {
    word32 instruction = MUL_FORMAT;
    int rd = tokens.operands[0][REG_NUM];
    int rm = tokens.operands[1][REG_NUM];
    int rs = tokens.operands[2][REG_NUM];
    
    if (!strcmp(tokens.opcode, "mla")) {
        instruction |= A_BIT;
        int rn = tokens.operands[3][REG_NUM];
        instruction |= rn << RN_POS;
    }
    
    instruction |= rm;
    instruction |= rd << RD_POS;
    instruction |= rs << RS_POS;
    return instruction;
} 




