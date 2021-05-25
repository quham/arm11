#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "em_general.h"

// print for debugging
void printMemory(uint8_t *a)
{
  printf("Hex representation:");
  for (int i = 0; a[i] != 0; i++)
  {
    if (i % 8 == 0)
    {
      printf(" ");
    }
    printf("%x ", a[i]);
  }
  printf("\n");
}

int main(int argc, char **argv)
{

  if (argc != 2)
  {
    perror("Invalid arguments! \n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  file = fopen(argv[1], "rb");

  if (file == NULL)
  {
    perror("File is null! \n");
    exit(EXIT_FAILURE);
  }

  //byte addressable memory using uint8_t type
  uint8_t memory[MEMORY_SIZE] = {0};
  fread(memory, sizeof(uint8_t), MEMORY_SIZE, file);
  fclose(file);

  printMemory(memory);
  return EXIT_SUCCESS;
}
