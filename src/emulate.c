#include <stdlib.h>
#include <em_general.h>



int main(int argc, char **argv) {


  //need to check if its a binary file! 
  if (argc != 2) {
    perror("Invalid arguments! \n");
    return EXIT_FAILURE;
  } 

  FILE *file = fopen(argv[1], "rb");

  if (file == NULL) {
    perror("File is null! \n");
    return EXIT_FAILURE;
  }


  memory[MEMORY_SIZE];

  char words[];


  fgets(memory, MEMORY_SIZE, file)







    return EXIT_SUCCESS;
}
