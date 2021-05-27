#include <stdlib.h>
#include "ass_general.h"
#include "symbol_table.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    perror("Invalid arguements! \n");
    exit(EXIT_FAILURE);
  }

  FILE *assembly;
  assembly = fopen(argv[1], "r");

  FILE *binary;
  binary   = fopen(argv[2], "w");

  if (assembly == NULL || binary == NULL) {
    perror("A file is null! \n");
    exit(EXIT_FAILURE);
  }
  

  //TODO: perform two passes on assembly file
  //TODO: write to binary file
  

  fclose(assembly);
  fclose(binary);
  return EXIT_SUCCESS;
}
