#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"

#define MAX_CHAR_LIMIT 128
#define CMD_INDEX 0

extern char *path;

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

void print_array(char **args, int num_args) {
  for (int i = 0; i < num_args; i++) {
    printf("%s\n", args[i]);
  }
}

void execute_external_cmd(char **args, int num_args) {
  char **p = args++; // do this when you need to cut off the first element
  char *fullpath = path;
  // fullpath = strcat(fullpath, args[0]);
  //  printf("path: %s, args[0]: %s\n", fullpath, args[0]);
  //   if (access(args[0], X_OK) == 0) {
  //    do nothing for now
  //   }
}

int split_arguments(char *input, char **args) {
  char *token = strtok(input, " ");
  int argument_count = 0;

  for (int i = 0; token != NULL; i++) {
    args[i] = token;
    token = strtok(NULL, " ");
    argument_count++;
  }
  return argument_count;
}

void interactive_mode() {
  printf("wish> ");

  char input[MAX_CHAR_LIMIT];
  fgets(input, MAX_CHAR_LIMIT, stdin);

  // split up the string
  char *arguments[MAX_CHAR_LIMIT];
  int argument_count = split_arguments(input, arguments);

  if (identify_built_in_cmd(arguments, argument_count) == 1)
    execute_external_cmd(arguments, argument_count);
}

void batch_mode(char filename[]) {
  FILE *fp;
  char line[MAX_CHAR_LIMIT];

  // opening file for reading
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file");
  }
  while (fgets(line, MAX_CHAR_LIMIT, fp) != NULL) {
    // split up the string
    char *arguments[MAX_CHAR_LIMIT];
    int argument_count = split_arguments(line, arguments);

    if (identify_built_in_cmd(arguments, argument_count) == 1)
      execute_external_cmd(arguments, argument_count);
  }
  fclose(fp);
}
