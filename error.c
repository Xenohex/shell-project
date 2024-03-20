#include "error.h"
#include <stdio.h>
#include <stdlib.h>

// prints an error message if error code is non-fatal.
// otherwise, ends the program
void error(int code) {
  fprintf(stderr, "An error has occurred\n");
  if (code == FATAL_ERROR)
    exit(1);
}
