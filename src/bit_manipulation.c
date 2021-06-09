#include "arm_general.h"

void setBit(word32 *word, int index) {
  *word |= 1 << index;
}

// inclusive start_index, exclusive end_index, indices start from LSB to MSB
word32 getBits(word32 word, int start_index, int end_index) {
  word32 mask = UINT32_MAX >> (WORD_SIZE - (end_index - start_index));
  return (word >> start_index) & mask;
}
