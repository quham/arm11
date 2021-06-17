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

  FILE *ass_file = fopen(argv[1], "r");
  if (ass_file == NULL) {
    perror("Error: Source input file is null\n");
    exit(EXIT_FAILURE);
  }

  // Create symbol table and count file lines (first pass)
  Table *sym_table = makeTable();
  word32 code_line = 0;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, ass_file)) {  // fgets unsafe
    char *label_end = strchr(line, ':');        // TODO: unsafe?
    if (label_end) {
      *label_end = '\0';
      put(sym_table, line, code_line * BYTES_PER_WORD);
    } else if (line[0] != '\n') {
      code_line++;
    }
  }
  safeSeek(ass_file, 0);

  FILE *bin_file = fopen(argv[2], "w");
  if (bin_file == NULL) {
    perror("Error: Bin_fileary output file is null\n");
    exit(EXIT_FAILURE);
  }

  assemble(ass_file, bin_file, sym_table, code_line);  // Second pass

  freeTable(sym_table);
  fclose(ass_file);
  fclose(bin_file);
  return EXIT_SUCCESS;
}

// TODO: use opcode map
void assemble(FILE *ass_file, FILE *bin_file, Table *sym_table, word32 ass_lines) {
  char line[LINE_LENGTH];
  word32 bin_lines = ass_lines;
  word32 line_num = 0;
  while (line_num < ass_lines) {
    if (!fgets(line, LINE_LENGTH, ass_file)) {
      perror("Error: assembly line read failed\n");
      exit(EXIT_FAILURE);
    }
    if (strchr(line, ':') || line[0] == '\n') {  // skip labels / blank lines
      continue;
    }
    line[strlen(line) - 1] = '\0';
    tokenset tokens = tokenize(line);
    printTokens(tokens);
    instr binary;
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
        binary = singleDataTransfer(tokens, bin_file, &bin_lines);
        break;
      case 's':
        if (!strcmp(tokens.opcode, "str")) {
          binary = singleDataTransfer(tokens, bin_file, &bin_lines);
        } else {
          binary = dataProcessing(tokens);
        }
        break;
      default:
        binary = dataProcessing(tokens);
    }
    fwrite(&binary, sizeof(instr), 1, bin_file);
    line_num++;
  }
}
