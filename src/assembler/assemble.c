#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

#define LINE_LENGTH 511
void printBits(word32 x) {
  int i;
  word32 mask = 1 << 31;
  for (i = 0; i < 32; ++i) {
    if (i % 4 == 0)
      printf(" ");
    if ((x & mask) == 0) {
      printf("0");
    } else {
      printf("1");
    }
    x = x << 1;
  }
  printf("\n ");
}

int main(int argc, char **argv) {
  /*char line[] = "mov r2, #4128768";
  tokenset tokens = tokenize(line);
  printTokens(tokens);
  printf("\n");
  word32 binary = dataProcessing(tokens);
  printBits(binary);*/

  if (argc != 3) {
    perror("Error: Invalid arguments\n");
    // exit(EXIT_FAILURE);
  }

  FILE *assembly;
  assembly = fopen(argv[1], "r");

  FILE *bin;
  bin = fopen(argv[2], "w");

  if (assembly == NULL || bin == NULL) {
    perror("Error: A file is null\n");
    exit(EXIT_FAILURE);
  }

  fseek(assembly, 0, SEEK_END);
  const int NUM_OF_LINES = ftell(assembly);
  char asm_lines[NUM_OF_LINES][LINE_LENGTH];
  fseek(assembly, 0, SEEK_SET);

  int i = 0;
  while (fgets(asm_lines[i], LINE_LENGTH, assembly)) {
    asm_lines[i][strlen(asm_lines[i]) - 1] = '\0';
    i++;
  }

  // printf("Lines to convert:\n\n");  // prints tokenset of each assembly line
  // for (int j = 0; j < i; j++) {
  //   tokenset tokens = tokenize(asm_lines[j]);
  //   printTokens(tokens);
  //   printf("\n");
  // }

  Table *sym_table = symbolise(asm_lines, i);  // TODO create a table (FIRST PASS)
  assemble(asm_lines, bin, sym_table, i);      // need number op
  // TODO: fix assemble
  // TODO write to binary file using mapping from symbolise (SECOND PASS)

  fclose(assembly);
  fclose(bin);
  return EXIT_SUCCESS;
}

Table *symbolise(char asm_lines[][LINE_LENGTH], int lines) {
  Table *table = makeTable();
  for (int i = 0; i < lines; i++) {
    char *str = strtok(asm_lines[i], ":");
    if (str != NULL) {
      put(table, (Pair){str, i * 4});
    }
  }
  return table;
}

void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table *table, int lines) {
  for (int i = 0; i < lines; i++) {
    if (!strchr(asm_lines[i], ':')) {
      instr binary = 0;
      tokenset tokens = tokenize(asm_lines[i]);
      printTokens(tokens);
      switch (tokens.opcode[0]) {
        case 'b':
          binary = branch(tokens, (word32)i * 4, table);
          break;
        case 'm':
          if (!strcmp(tokens.opcode, "mov")) {
            binary = dataProcessing(tokens);
          } else {
            binary = multiply(tokens);
          }
          break;
        case 'l':
          // binary = singleDataTransfer(tokens);
          break;
        case 's':
          if (!strcmp(tokens.opcode, "str")) {
            // binary = singleDataTransfer(tokens);
          } else {
            binary = dataProcessing(tokens);
          }
          break;
        default:
          printf("processing\n");
          binary = dataProcessing(tokens);
      }
      fwrite(&binary, sizeof(instr), 1, binary_file);
    }
  }
  freeTable(table);
}
