#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

// TODO: deal with blank lines
int main(int argc, char **argv) {
  if (argc != 3) {  // Number of arguments main takes
    perror("Error: Invalid arguments\n");
    exit(EXIT_FAILURE);
  }

  FILE *assembly_file = fopen(argv[1], "r");
  if (assembly_file == NULL) {
    perror("Error: Source input file is null\n");
    exit(EXIT_FAILURE);
  }

  // Create symbol table and count file lines (first pass)
  Table *sym_table = makeTable();
  word32 line_num = 0;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, assembly_file)) {  // fgets unsafe
    line_num++;
    char *label_end = strchr(line, ':');  // unsafe?
    if (label_end) {
      *label_end = '\0';
      put(sym_table, (Pair){line, line_num * 4});
    }
  }
  if (fseek(assembly_file, 0, SEEK_SET)) {
    perror("Error: Seek source file start failed\n");
    exit(EXIT_FAILURE);
  }

  FILE *bin = fopen(argv[2], "w");
  if (bin == NULL) {
    perror("Error: Binary output file is null\n");
    exit(EXIT_FAILURE);
  }

  assemble(assembly_file, bin, sym_table, line_num);  // Second pass

  fclose(assembly_file);
  fclose(bin);
  return EXIT_SUCCESS;
}

// TODO: use opcode map
// Bug: num_of_lines is for assembly but we need for binary (no because they are same?)
void assemble(FILE *assembly_file, FILE *binary_file, Table *sym_table, word32 num_of_lines) {
  char line[LINE_LENGTH];
  for (size_t i = 0; fgets(line, LINE_LENGTH, assembly_file) && !strchr(line, ':'); i++) {
    line[strlen(line) - 1] = '\0';  // safe?
    instr binary = 0;
    tokenset tokens = tokenize(line);
    printTokens(tokens);
    switch (tokens.opcode[0]) {
      case 'b':
        binary = branch(tokens, i * 4, sym_table);
        break;
      case 'm':
        if (!strcmp(tokens.opcode, "mov")) {
          binary = dataProcessing(tokens);
        } else {
          binary = multiply(tokens);
        }
        break;
      case 'l':
        binary = singleDataTransfer(tokens, binary_file, &num_of_lines);
        break;
      case 's':
        if (!strcmp(tokens.opcode, "str")) {
          binary = singleDataTransfer(tokens, binary_file, &num_of_lines);
          fseek(binary_file, i, SEEK_SET);
        } else {
          binary = dataProcessing(tokens);
        }
        break;
      default:
        binary = dataProcessing(tokens);
    }
    fwrite(&binary, sizeof(instr), 1, binary_file);
  }
  freeTable(sym_table);
}
