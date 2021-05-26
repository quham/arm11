#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "em_general.h"

enum itype{PROCESSING,MULTIPLY, TRANSFER , BRANCH, TERMINATE};

void pipeline(struct State* state){
    word32 decoded = NOTINIT;
    word32 fetched = NOTINIT;
    enum itype type;
    while(1){
        if (decoded != NOTINIT ){
            execute(decoded, type, state , &decoded, &fetched);
        }if (fetched != NOTINIT){
            decoded = fetched;
            type = decode(fetched);
        }
        fetched = fetch(state->registers[PC]);
        state->registers[PC] += 4;
    }
    // while not end - 0 instruction
    //executes decoded instruction if not null;
    //decodes fetched instruction if not null;
    //fetch next instruction incrementing pc



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
            if(!getBits(instruction, 22 , 25) & !(getBits(instruction, 4,7) ^ 1001)){
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
            *decoded = NOTINIT;
            *fetched = NOTINIT;
            break;
        default:
            exit(EXIT_SUCCESS);//exits function? should i print here?


            
    }

    //stores next decoded inatruction also executes last decode instruction based on itype case switch
    //case where instruction all 0 needs to set end to true. Take end as parameter?
    //executing branch requires current fetch and decode to be cleared
}
