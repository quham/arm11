#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ass_general.h"

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
  word32 code_line = 0;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, assembly_file)) {  // fgets unsafe
    char *label_end = strchr(line, ':');             // unsafe?
    if (label_end) {
      *label_end = '\0';
      put(sym_table, line, code_line * BYTES_PER_WORD);
    } else if (line[0] != '\n') {
      code_line++;
    }
  }
  safeSeek(assembly_file, 0);

  FILE *bin = fopen(argv[2], "w");
  if (bin == NULL) {
    perror("Error: Binary output file is null\n");
    exit(EXIT_FAILURE);
  }

  assemble(assembly_file, bin, sym_table, code_line);  // Second pass

  fclose(assembly_file);
  fclose(bin);
  return EXIT_SUCCESS;
}

// TODO: use opcode map
void assemble(FILE *assembly_file, FILE *binary_file, Table *sym_table, const word32 assembly_lines) {
  char line[LINE_LENGTH];
  word32 binary_lines = assembly_lines;
  word32 line_num = 0;
  while (line_num < assembly_lines) {
    if (fgets(line, LINE_LENGTH, assembly_file) == NULL) {
      perror("Error: assembly line read failed\n");
      exit(EXIT_FAILURE);
    }
    if (strchr(line, ':') || line[0] == '\n') {  // skip labels / blank lines
      continue;
    }
    line[strlen(line) - 1] = '\0';
    tokenset tokens = tokenize(line);
    printTokens(tokens);
    instr binary ;
    switch (tokens.opcode[0]) {
      case 'b':
        binary = branch(tokens, line_num * BYTES_PER_WORD, sym_table);
        break;
      case 'm':
        if (!strcmp(tokens.opcode, "mov")) {
          binary = dataProcessing(tokens);
        } else {
          binary = multiply(tokens);
        }
        break;
      case 'l':
        binary = singleDataTransfer(tokens, binary_file, &binary_lines);
        break;
      case 's':
        if (!strcmp(tokens.opcode, "str")) {
          binary = singleDataTransfer(tokens, binary_file, &binary_lines);
        } else {
          binary = dataProcessing(tokens);
        }
        break;
      default:
        binary = dataProcessing(tokens);
    }
    fwrite(&binary, sizeof(instr), 1, binary_file);
    line_num++;
  }
  freeTable(sym_table);
}
