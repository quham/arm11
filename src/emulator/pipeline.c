#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "em_general.h"

enum itype{PROCESSING,MULTIPLY, TRANSFER , BRANCH, TERMINATE};

void pipeline(struct State* state){
    word32 decoded = NOT_INIT;
    word32 fetched = NOT_INIT;
    enum itype type;
    while(1){
        if (decoded != NOT_INIT ){
            execute(decoded, type, state , &decoded, &fetched);
        }if (fetched != NOT_INIT){
            decoded = fetched;
            type = decode(fetched);
        }
        fetched = fetch(state->registers[PC_INDEX]);
        state->registers[PC_INDEX] += 4;
    }



}
word32 fetch ( word32 pc, struct State* state ){ //returns instruction
    return state->memory[pc];
}
enum itype decode(word32 instruction){//return type?
    switch(getBits(instruction, 26 , 27)){
        case 2:
            return BRANCH;
        case 1:
            return TRANSFER;
        case 0:
            if(!getBits(instruction, 22 , 25) && !(getBits(instruction, 4,7) ^ 1001)){
                // extracts bits 4-7 xor with 1001 to check for multiply format
                return MULTIPLY
            }else if (!instruction) {
                return TERMINATE;
            }else{
                return PROCESSING;
            }
        default:
            perror("Invalid instruction type"); //needs to terminate here

    }

    }

}
word32 execute(word32 instruction, enum itype type , struct State* state , word32* decoded , word32* fetched){
    switch(type){
        case PROCESSING:
            data_processing(instruction,state);
            break;
        case MULTIPLY:
            multiply(instruction,state);
            break;
        case TRANSFER:
            single_data_transfer(instruction, state);
            break;
        case BRANCH:
            branch(instruction, state);
            *decoded = NOT_INIT;
            *fetched = NOT_INIT;
            break;
        default:
            exit(EXIT_SUCCESS);//exits function? should i print here?


            
    }

}
