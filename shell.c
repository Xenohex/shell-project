#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "error.h"

#define MAX_CHAR_LIMIT 128
#define CMD_INDEX 0

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
  //   create the target path
  char fullpath[MAX_CHAR_LIMIT];
  strcpy(fullpath, return_path());
  // create a copy of args[0]
  char cmd[MAX_CHAR_LIMIT];
  strcpy(cmd, args[0]);

  // concatenate path
  strcpy(cmd, strcat(fullpath, cmd));

  //  check if accesss to command exists, if so, execute it
  if (access(cmd, X_OK) == 0) {
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
    error();
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

// ./wish with no arguments
void interactive_mode() {
  printf("wish> ");

  char input[MAX_CHAR_LIMIT];
  fgets(input, MAX_CHAR_LIMIT, stdin);

  remove_newline(input);

  // split up the string
  char *arguments[MAX_CHAR_LIMIT];
  int argument_count = split_arguments(input, arguments);

  // arguments[0] = remove_newline(arguments[0]);

  if (identify_built_in_cmd(arguments, argument_count) == 1)
    execute_external_cmd(arguments, argument_count);
}

// ./wish <filename>
void batch_mode(char filename[]) {
  FILE *fp;
  char line[MAX_CHAR_LIMIT];

  // opening file for reading
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file");
  }
  while (fgets(line, MAX_CHAR_LIMIT, fp) != NULL) {

    remove_newline(line);
    // split up the string
    char *arguments[MAX_CHAR_LIMIT];
    int argument_count = split_arguments(line, arguments);

    if (identify_built_in_cmd(arguments, argument_count) == 1)
      execute_external_cmd(arguments, argument_count);
  }
  fclose(fp);
}
