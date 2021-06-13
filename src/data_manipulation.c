#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm_general.h"

void setBit(word32* word, int index) {
  *word |= 1 << index;
}

// inclusive start_index, exclusive end_index, indices start from LSB to MSB
word32 getBits(word32 word, int start_index, int end_index) {
  word32 mask = UINT32_MAX >> (WORD_SIZE - (end_index - start_index));
  return (word >> start_index) & mask;
}

void safeStrCpy(char* dest, char* src) {  // TODO: use stncpy
  strcpy(dest, src);
  assert(dest[strlen(dest)] == '\0');
}

void safeStrCat(char* dest, char* src) {
  strcat(dest, src);
  assert(dest[strlen(dest)] == '\0');
}

void safeSeek(FILE* file, word32 line) {
  if (fseek(file, line, SEEK_SET)) {
    perror("Error: Seek file line failed\n");
    exit(EXIT_FAILURE);
  }
}
