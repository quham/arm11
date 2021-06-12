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
  word32 line_num = 0;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, assembly_file)) {  // fgets unsafe
    char *label_end = strchr(line, ':');             // unsafe?
    if (label_end) {
      *label_end = '\0';
      printf("line to put %s\n", line);
      put(sym_table, line, line_num * 4);
    }
    line_num++;
  }
  safeSeek(assembly_file, 0);

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
void assemble(FILE *assembly_file, FILE *binary_file, Table *sym_table, word32 file_lines) {
  char line[LINE_LENGTH];
  const word32 code_lines = file_lines;
  for (word32 i = 0; i < code_lines; i++) {
    fgets(line, LINE_LENGTH, assembly_file);
    if (strchr(line, ':')) {  // skip labels
      continue;
    }
    line[strlen(line) - 1] = '\0';
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
        binary = singleDataTransfer(tokens, binary_file, &file_lines);
        break;
      case 's':
        if (!strcmp(tokens.opcode, "str")) {
          binary = singleDataTransfer(tokens, binary_file, &file_lines);
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
