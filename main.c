/*
Original Author: Austin Pliska
Traded with: Kevin Pickelman
*/

#include "error.h"
#include "shell.h"

#define NO_ARGUMENTS 1
#define ONE_ARGUMENT 2

int main(int argc, char *argv[]) {
  while (argc == NO_ARGUMENTS) // interactive mode
    interactive_mode();        // program exits from here
  if (argc == ONE_ARGUMENT) {  // batch file
    batch_mode(argv[1]);
  } else { // too many arguments
    error(FATAL_ERROR);
    // error_test(FATAL_ERROR, "main.c: too many arguments");
  }

  return 0;
}
