#include <stdio.h>


#include <stdlib.h>



int main(int argc, char **argv) {


  //need to check if its a binary file! 
  if (argc != 2) {
    perror("Invalid arguments! \n");
    return -1;
  } 

  FILE *file = fopen(argv[1], "rb");

  if (file == NULL) {
    perror("File is null! \n");
    return -1;
  }


  memory[MEMORY_SIZE];


  fread(memory, MEMORY_SIZE, file)







    return 0;
}

    
