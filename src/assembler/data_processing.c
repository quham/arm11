#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ass_general.h"

#define DP_FORMAT 0xe0000000
#define I_FLAG 0x02000000
#define S_FLAG 0x00010000
#define ROTATION_OFFSET 8
#define SHIFT_OFFSET 4
#define SHIFT_OPERAND_OFFSET 3
#define OPCODE_OFFSET 20
#define SHIFT_TYPE_OFFSET 1
//const char* compute_results = {"and", "eor", "sub", "rsb", "add", "orr"};
//const char* not_compute_results = {"tst", "teq", "cmp"};

void printBits(word32 x) { int i;
word32 mask = 1 << 31;
 for(i=0; i<32; ++i) {
   if (i % 4 == 0) 
     printf(" ");
   if((x & mask) == 0){
     printf("0");
   } else {
     printf("1");
   }
  x = x << 1;
 }
 printf("\n ");
 
}
/*
int main(void) {
  char *str = "sub r1, r2, r3, lsl r4";
  printf("1\n");
  tokenset tokens = tokenize(str);
  //word32 instruction = dataProcessing(&tokens);
  //printBits(instruction);
  printf("0\n");
  return 0;
}
*/
word32 dataProcessing(tokenset *tokens) {
  word32 instruction = DP_FORMAT;
  word32 opcode = getOpcode(&instruction, tokens->opcode);
  setOperand(&instruction, tokens->operands + 2 * LINE_LENGTH);
  instruction |= opcode << OPCODE_OFFSET;
  // mov is thecked first so we can distinguis between add
  // and tst (and others) instructions and set S flag if needed
  
    
  return instruction;
}

//function takes just third and fourth agruments
void setOperand(word32 *instruction, char operands[2][LINE_LENGTH]) {

  if (operands[0][0] == '#') {
    setExpression(instruction, strtol(operands[0] + 1, NULL, 0)); // ignores # and converts all to long
  } else {
    byte rm = atoi(operands[0] + 1); //ignores r and gets the reg number  
    byte shift = 0;
    if (operands[1] != NULL) { // whether there is a shift
      char **save_ptr = NULL;
      char *shift_type, *shift_operand;
      shift_type = strtok_r(operands[1], " ", save_ptr);
      shift_operand = strtok_r(NULL, " ", save_ptr);
      word32 shift_op;
      word32 shift_t = getShiftTypeInt(shift_type);

      // this if-else sets shift operand
      if (shift_operand[0] == '#') { 
	shift_op = strtol(shift_operand + 1, NULL, 0);
	if (shift_op >= 64) {
	  perror("Error: Shift-operand value is too big\n");
	  exit(EXIT_FAILURE);
	}
      } else {
	shift |= 1; // sets 4 bit as for register shift
	shift_op = atoi(shift_operand + 1);
	shift_op <<= 1; // so takes 5 bits as immediate
      }
      
      shift |= shift_t << SHIFT_TYPE_OFFSET;
      shift |= shift_op << SHIFT_OPERAND_OFFSET;
      
    }
    *instruction |= rm;
    *instruction |= shift << SHIFT_OFFSET;
  }
  return;
}

// Function ecnodes a numeric constant.
// If number is less then 256, then we can surely encode it,
// otherwise we migh need to rotate until we find a one on LSB
// and compare to 256 again, but aslo include rotation bits or
// print an error.
void setExpression(word32 *instruction, word32 expression) {
  *instruction |= I_FLAG;
  
  word32 rotation = 0;
  if (expression < 256) {
    *instruction |= expression;
  }
  
  while(!(expression & 1)) { // shifts and compares LSB with 1
      expression >>= 1;
      rotation++;
    }
  if (expression < 256) {
    rotation = 32 - rotation; // full rotation should be made,so leftovers are encoded
    *instruction |= expression;
    *instruction |= rotation << ROTATION_OFFSET;
  } else {
    perror("Error: Immediate value does not fit in 8 bits\n");
    exit(EXIT_FAILURE);
  }
  return;   
}
    
byte getShiftTypeInt(const char *str) {
  if (!strcmp(str, "lsl"))
    return 0;
  if (!strcmp(str, "lsr"))
    return 1;
  if (!strcmp(str, "asr"))
    return 2;
  if(!strcmp(str, "ror"))
    return 3;
  perror("Error: Strange type for getShiftTypeInt, data_processing\n");
  exit(EXIT_FAILURE);
}

byte getOpcode(word32 *instruction, const char *str) {
  if (!strcmp(str, "and"))
    return 0;
  if (!strcmp(str, "eor"))
    return 1;
  if (!strcmp(str, "sub"))
    return 2;
  if (!strcmp(str, "rsb"))
    return 3;
  if (!strcmp(str, "add"))
    return 4;
  if (!strcmp(str, "tst")) {
    *instruction |= S_FLAG;
    return 8;
  }
  if (!strcmp(str, "teq")) {
    *instruction |= S_FLAG;
    return 9;
  }
  if (!strcmp(str, "cmp")) {
    *instruction |= S_FLAG;
    return 10;
  }
  if (!strcmp(str, "orr"))
    return 12;
  if (!strcmp(str, "mov"))
    return 13;
  perror("Error: Unsupported opcode\n");
  exit(EXIT_FAILURE);
}
