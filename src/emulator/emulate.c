#include <stdlib.h>
#include <stdint.h>
#include "em_general.h"

void pipeline(uint8_t*);
//instr is 4 byte long 
typedef uint32_t instr;

int main(int argc, char **argv) {

  //need to check if its a binary file! 
  if (argc != 2) {
    perror("Invalid arguments! \n");
    exit(EXIT_FAILURE);
  } 

  FILE *file;
  file = fopen(argv[1], "rb");
  
  if (file == NULL) {
    perror("File is null! \n");
    exit(EXIT_FAILURE);
  }

  //byte addressable memory using uint8_t type 
  uint8_t memory[MEMORY_SIZE] = {0};
  fread(memory, sizeof(uint8_t), MEMORY_SIZE, file);
  fclose(file);

  
  pipeline(memory); 
  return EXIT_SUCCESS;
}

void pipeline(uint8_t *a) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%u\n", a[i]);
    }
}
