#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "error.h"

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

void remove_newline(char *text) {
  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == '\n') {
      text[i] = '\0';
    }
  }
  // print_chars(text);
}

// if command cannot be found in internal files, search path for it
void execute_external_cmd(char **args, int num_args) {
  int cmd_found = 0; // if cmd_found is set to 1, the command is found

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
    printf("Fullpath: %s\n", fullpath); // REMOVE

    //  check if accesss to command exists, if so, execute it
    if (access(cmd, X_OK) == 0) {
      // access granted
      cmd_found = 1; // ensures the loop won't check any more paths

      // todo insert pipe around here somewhere

      int rc = fork();
      if (rc < 0) {
        // fork failed; exit
        error();
        exit(1);
      } else if (rc == 0) {
        // child (new process)
        execv(cmd, args);
      } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
      }
    } else {
      if (path_counter == (path_count - 1))
        error(); // if there are multiple paths, only errors if it never finds
                 // command through all paths
    }
  }
}

// split the given arguments into separate pieces
int split_arguments(char *input, char **args) {
  char *token = strtok(input, " ");
  int argument_count = 0;

  for (int i = 0; token != NULL; i++) {
    args[i] = token;
    token = strtok(NULL, " ");
    argument_count++;
  }
  args[argument_count] = NULL;
  return argument_count;
}

/*
return -1 for no redirection.
if return 0, call error
if return > 0, that is the index of the argument with the redirection operator
*/
int check_for_redirection(char **args, int num_args) {
  char *redirection;
  int r_index = -1;
  int redirection_found = 0;

  for (int i = 0; i < num_args; i++) {
    if (strchr(args[i], '>') != NULL) {
      if (redirection_found == 1) {
        error();
        break;
      }
      r_index = i;
      redirection_found = 1;
    }
  }
  if (r_index == num_args - 1 &&
      args[r_index][strlen(args[r_index]) - 1] == '>') {
    error(); // if redirection operator is the last (or only) character in the
             // last argument
  }

  return r_index;
}

void redirect(char **args, int num_args, char filename[]) { // todo make this
  FILE *fp;
  char line[MAX_CHARS];

  if (access(filename, F_OK) != 0)
    truncate(filename, 0); // deletes everything in the file

  // opening file for reading
  fp = fopen(filename, "w");
  if (fp == NULL) {
    error();
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

// ./wish with no arguments
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

// ./wish <filename>
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
