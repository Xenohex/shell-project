#include "commands.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "shared.h"

char path[MAX_ARGS][MAX_CHARS] = {DEFAULT_PATH};
int path_count = 1; // should never be 0

// exits the program with successful code
void cmd_exit(char **text, int num_args) {
  if (num_args > 1) {
    if (str_is_empty(text[1]) == 0)
      exit(0);
    error(NON_FATAL_ERROR);
    // error_test(NON_FATAL_ERROR, "cmd_exit: exit failed?");
  } else {
    exit(0);
  }
}

// chooses a new current working directory for the program
void cmd_cd(char **args, int num_args) {
  if (chdir(args[1]) != 0)
    error(NON_FATAL_ERROR);
  // error_test(NON_FATAL_ERROR, "cmd_cd: failed");
}

// chooses one or multiple possible paths to search for executables
void cmd_path(char **args, int num_args) {
  if (num_args < 2) {
    strcpy(path[0], "");
    path_count = 1;
  } else {
    for (int i = 1; i < num_args; ++i) {
      strcpy(path[i - 1], args[i]); // copy argument text to path
      if (path[i - 1][strlen(path[i - 1]) - 1] !=
          '/') {                  // check if '/' is at the end of the path
        strcat(path[i - 1], "/"); // Concatenate '/' to the end of the path
      }
    }
    path_count = num_args - 1;
  }
}
