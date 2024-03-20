#include "shell.h"

#include <stdio.h> // REMOVE?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "error.h"
#include "redirection.h"
#include "shared.h"

#define CMD_INDEX 0

extern char path[MAX_ARGS][MAX_CHARS];
extern int path_count;

// return 0 if command is built in, 1 if not
int identify_built_in_cmd(char **args, int num_args) {

  if (strncmp(args[CMD_INDEX], "exit", 4) == 0) {
    cmd_exit(args, num_args);
    return 0; // built-in command found
  } else if (strncmp(args[CMD_INDEX], "path", 4) == 0) {
    cmd_path(args, num_args);
    return 0; // built-in command found
  } else if (strncmp(args[CMD_INDEX], "cd", 2) == 0) {
    cmd_cd(args, num_args);
    return 0; // built-in command found
  }
  return 1; // command is not built-in
}

// if command cannot be found in internal files, search path for it
void execute_external_cmd(char **args, int num_args) {

  int r_index = find_redirection(args, num_args);
  printf("r_index: %d\n", r_index);
  find_redirection_type(args, num_args, r_index);

  int cmd_found = 0; // if cmd_found is set to 1, the command is found
  int link[2];       // for piping/redirection

  // loop through all paths
  for (int path_counter = 0; path_counter < path_count && cmd_found != 1;
       path_counter++) {

    // create the target path
    char fullpath[MAX_CHARS];
    strcpy(fullpath, path[path_counter]);

    // create a copy of args[0]
    char cmd[MAX_CHARS];
    strcpy(cmd, args[0]);

    // concatenate path
    strcpy(cmd, strcat(fullpath, cmd));

    //  check if accesss to command exists, if so, execute it
    if (access(cmd, X_OK) == 0) {
      // access granted
      cmd_found = 1; // ensures the loop won't check any more paths

      // todo insert pipe around here somewhere

      int rc = fork();

      if (rc < 0) {
        // fork failed; exit
        error(FATAL_ERROR);
      } else if (rc == 0) {
        // child (new process)

        execv(cmd, args);
      } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
      }
    } else { // access fails
      if (path_counter == (path_count - 1))
        error(NON_FATAL_ERROR); // if there are multiple paths, only errors if
                                // it never finds command through any of the
                                // given paths
    }
  } // end loop
}

// ./wish with no arguments, runs until exited by user or fatal error
void interactive_mode() {
  printf("wish> ");

  char input[MAX_CHARS];
  fgets(input, MAX_CHARS, stdin);

  remove_newline(input);

  // split up the string
  char *arguments[MAX_CHARS];
  int argument_count = split_arguments(input, arguments);

  // arguments[0] = remove_newline(arguments[0]);

  if (identify_built_in_cmd(arguments, argument_count) == 1)
    execute_external_cmd(arguments, argument_count);
}

// ./wish <filename>, interactive mode with predefined commands. runs until exit
// call or end of file
void batch_mode(char filename[]) {
  FILE *fp;
  char line[MAX_CHARS];

  // opening file for reading
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file");
  }
  while (fgets(line, MAX_CHARS, fp) != NULL) {

    remove_newline(line);
    // split up the string
    char *arguments[MAX_CHARS];
    int argument_count = split_arguments(line, arguments);

    if (identify_built_in_cmd(arguments, argument_count) == 1)
      execute_external_cmd(arguments, argument_count);
  }
  fclose(fp);
}
