#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void error(int code) {
  fprintf(stderr, "An error has occurred\n");
  if (code == FATAL_ERROR)
    exit(1);
}
