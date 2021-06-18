#include <stdint.h>
#include <stdlib.h>

#include "ass_general.h"

void updateBits(word32 *word, int index, word32 value) {
  *word |= value << index;
}

byte regNumber(char *reg_token) {
  return strtol(reg_token + 1, NULL, 10);
}

word32 readHex(char *hex) {
  return strtol(hex, NULL, 0);
}

void setCondCodeFlag(instr *instruction) {
  setBit(instruction, 20);
}

void setImmediate(instr *instruction) {
  setBit(instruction, 25);
}

void updateRm(instr *instruction, byte rm) {
  updateBits(instruction, 0, rm);
}

word32 relativeAddr(word32 target, word32 pc) {
  return target - pc - PC_PIPELINE_OFFSET;
}
