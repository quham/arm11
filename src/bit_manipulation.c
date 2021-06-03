#include "arm_general.h"

void setBit(word32 *word, int index) {
  *word |= 1 << index;
}