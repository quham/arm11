#include <stdint.h>
#include "em_general.h"
#include "instr_decompose.c"
#include "data_processing.c"

void multiply(instr instruction, struct State *state) {

  if (condCode(instruction)) {
    return;
  }

  word32 set = checkSet(instruction);
  word32 acc = getBits(instruction, ACC_MASK, ACC_INDEX);
  word32 rd  = getBits(instruction, 0xf0000, 16); //extracting bits 16 to 20
  word32 rn  = getBits(instruction, 0xf000, 12);  //extracting bits 12 to 16
  word32 rm  = getBits(instruction, 0xf0000, 0);  //extracting bits 0 to 3
  word32 rs  = getBits(instruction, 0xf00, 8);    //extracting bits 8 to 12 

  if (acc) {
  } else {
  }
}
