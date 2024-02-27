#include "commands.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

char path[] = DEFAULT_PATH;

// return 0 if string length < 2, return 1 otherwise
int str_is_empty(char *str) {
  if (strlen(str) < 2)
    return 0;
  return 1;
}

void cmd_exit(char **text, int num_args) {
  if (num_args > 1) {
    if (str_is_empty(text[1]) == 0)
      exit(0);
    error();
  } else {
    exit(0);
  }
}

void cmd_cd(char **args, int num_args) {
  if (chdir(args[1]) != 0)
    error();
}

void cmd_path(char **args, int num_args) {
  if (num_args < 2) {
    strcpy(path, "");
  } else {
    strcpy(path, args[1]);
    if (path[strlen(path) - 1] != '/') {
      strcat(path, "/"); // Concatenate '/' to the end of the string
    }
  }
}

char *return_path() {
  // puts(path);
  return path;
}
