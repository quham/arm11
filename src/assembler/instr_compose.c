#include "ass_general.h"

void setBits(word32 *word, int index, word32 value) {
  *word |= value << index;
}

uint8_t regNumber(char *reg_token) {
  return strtoll(reg_token + 1, NULL, 10);
}