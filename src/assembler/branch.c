#include <stdio.h>
instr branch(tokens tokens, ) {
    word32 target;
    /*
    if (isLabel(tokens.operands[0]) ){//is alpha not digits
        target = getLabel(table, tokens.operands[0]));
    }else{
        target = tokens.operands[0];
    }*/
    word32 offset = (target - address - 8);
    word32 cond;
    switch (tokens.opcode[1]){
        case 'e':
            cond = 0x0fffffff;
            break;
        case 'n':
            cond = 0x1fffffff;
            break;
        case 'g':
            if(tokens.opcode[2] == 'e'){
                cond = 0xafffffff;
            }else{
                cond = 0xcfffffff;
            }
            break;
        case 'l':
            if(tokens.opcode[2] == 'e'){
                cond = 0xdfffffff;
            }else{
                cond = 0xbfffffff;
            }
            break;
        default:
            cond = 0xefffffff;
    }
    instr binary = offset & cond & 0xfaffffff;//branch syntax define as const
    return binary;

}