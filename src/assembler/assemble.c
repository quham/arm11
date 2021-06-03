#include "ass_general.h"
#include "symbol_table.h"
#include "tokenizer.h"

#define LINE_LENGTH 511

struct Table {
  char *test;
};
typedef struct Table Table;
Table symbolise(char asm_lines[][LINE_LENGTH]);
void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table);

int main(int argc, char **argv) {
  if (argc != 3) {
    perror("Error: Invalid arguements\n");
    exit(EXIT_FAILURE);
  }

  FILE *assembly;
  assembly = fopen(argv[1], "r");

  FILE *bin;
  bin = fopen(argv[2], "w");

  if (assembly == NULL || bin == NULL) {
    perror("Error: A file is null");
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

  printf("Lines to convert:\n\n");  // prints tokenset of each assembly line
  for (int j = 0; j < i; j++) {
    tokenset tokens = tokenize(asm_lines[j]);
    printTokens(tokens);
    printf("\n");
  }

  Table sym_table = symbolise(asm_lines);  // TODO create a symbol_table (FIRST PASS)
  assemble(asm_lines, bin, sym_table, NUM_OF_LINES);  
  // TODO write to binary file using mapping from symbolise (SECOND PASS)

  fclose(assembly);
  fclose(bin);
  return EXIT_SUCCESS;
}

Table symbolise(char asm_lines[][LINE_LENGTH]) {
  Table t = {0};
  return t;
}

void assemble(char asm_lines[][LINE_LENGTH], FILE *binary_file, Table symbol_table, int lines) {
    for (int i = 0 ; i < lines ; i++){
        if (!strchr(line, ':')) {
            instr binary;
            tokenset tokens = tokenize(asm_lines[i]);
            switch(tokens.opcode[0]){
                case 'b':
                    binary = branch(tokens);//pass symbol table?
                    break;
                case 'm':
                    if (tokens.opcode = "mov"){
                        binary = data_processing(tokens);
                    }else{
                        binary = multiply(tokens);
                    }
                    break;
                case 'l':
                    binary = single_data_transfer(tokens);
                    break;
                case 's':
                    if (tokens.opcode = "str") {
                        binary = single_data_transfer(tokens);
                    }else{
                        binary = data_processing(tokens);
                    }
                    break;
                default:
                    binary = data_processing(tokens);
            }
            fwrite(&binary , sizeof(instr), 1, binary_file);
        }


    }

}
