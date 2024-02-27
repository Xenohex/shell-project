#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1
#define DEFAULT_PATH "/bin/"

// todo this should eventually accept multiple paths
char *path = DEFAULT_PATH;

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

void cmd_cd(char **text, int num_args) {
  if (num_args < 2 || num_args > 3 ||
      (num_args == 3 && str_is_empty(text[2]) != 0))
    error();
  else {
    if (chdir(text[1]) != 0)
      error();
  }
  // print current active directory
  // char cwd[128];
  // if (getcwd(cwd, sizeof(cwd)) != NULL) {
  //   printf("Current working dir: %s\n", cwd);
  // } else {
  //   perror("getcwd() error");
  // }
}

void cmd_path(char **text, int num_args) {
  if (num_args == 2) {
    path = text[1];
    if (str_is_empty(text[1]) == 0)
      path = "/";
  } else if (num_args == 1) {
    path = DEFAULT_PATH;
  } else {
    // more path options not implemented yet
  }
}

// // prints all arguments excluding the command
// void cmd_echo(char **text, int num_args) {
//   for (int i = 1; i < num_args; i++) {
//     printf("%s", text[i]);
//     if (i != (num_args - 1))
//       printf(" ");
//   }
// }
