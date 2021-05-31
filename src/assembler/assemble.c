#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ass_general.h"
#include "symbol_table.h"

#define LINE_LENGTH 511
struct Table {};
typedef struct Table Table;
Table symbolise(char asm_lines[][LINE_LENGTH]);
void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table);

int main(int argc, char **argv) {

  if (argc != 3) {
    perror("Invalid arguements! \n");
    exit(EXIT_FAILURE);
  }

  FILE *assembly;
  assembly = fopen(argv[1], "r");

  FILE *bin;
  bin   = fopen(argv[2], "w");

  if (assembly == NULL || bin == NULL) {
    perror("A file is null! \n");
    exit(EXIT_FAILURE);
  }


  char asm_lines[LINE_LENGTH][LINE_LENGTH];

  int i = 0;
  while (fgets(asm_lines[i], LINE_LENGTH, assembly)) {
    asm_lines[i][strlen(asm_lines[i]) - 1] = '\0';
    i++;
  }

  printf("Lines to convert:\n\n"); // prints assembly lines
  for (int j = 0; j < i; j++) {
    printf("%s\n", asm_lines[j]);
  }  

  Table sym_table = symbolise(asm_lines); // TODO create a symbol_table (FIRST PASS)  
  assemble(asm_lines, bin, sym_table);    // TODO write to binary file using mapping from symbolise (SECOND PASS)
  
  fclose(assembly);
  fclose(bin);
  return EXIT_SUCCESS;
}


Table symbolise(char asm_lines[][LINE_LENGTH]) {
    Table t;
    return t;
}

void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table) {}
