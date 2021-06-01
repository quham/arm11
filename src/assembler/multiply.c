#include "ass_general.h"
#include "tokenizer.h"

#define MUL_FORMAT 0xe0000090
#define A_BIT 0x100000

uint32_t multiply(tokenset tokens) {
    uint32_t instruction = MUL_FORMAT;
    char *operand = tokens.operand;
    char *regs[4];


    char *reg = strtok(operand, ",");
    int i = 0;
    while (reg != NULL) {
        regs[i] = reg;
        reg = strtok(NULL, ",");
        i++;
    }

    if (!strcmp(tokens.opcode, "mla")) {
        instruction |= A_BIT;



    } else {


    }

    return instruction;
} 




