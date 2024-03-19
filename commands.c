#include "commands.h"
#include <stdio.h> // remove?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"

#define MAX_CHAR_LIMIT 128
#define MAX_PATHS = 32
#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

char path[MAX_ARGS][MAX_CHARS] = {DEFAULT_PATH};
int path_count = 1; // should never be 0

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

void print_array_pointer(char **args, int num_args) { // REMOVE
  printf("array: ");
  for (int i = 0; i < num_args; i++) {
    printf("%s ", args[i]);
  }
  puts("");
} // REMOVE

void print_array_array(char args[MAX_ARGS][MAX_CHARS], int num_args) { // REMOVE
  printf("array: ");
  for (int i = 0; i < num_args; i++) {
    printf("%s ", args[i]);
  }
  puts("");
} // REMOVE

void cmd_path(char **args, int num_args) {
  int arg_len = 0;
  if (num_args < 2) {
    strcpy(path[0], "");
    path_count = 1;
  } else {
    for (int i = 1; i < num_args; ++i) {
      strcpy(path[i - 1], args[i]); // copy argument text to path
      arg_len = strlen(args[i - 1]);
      if (path[i - 1][strlen(path[i - 1]) - 1] !=
          '/') {                  // check if '/' is at the end of the path
        strcat(path[i - 1], "/"); // Concatenate '/' to the end of the path
      }
    }
    path_count = num_args - 1;
  }
}
