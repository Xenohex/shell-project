#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "error.h"

#define MAX_CHAR_LIMIT 128
#define CMD_INDEX 0

void cmd_exit(char *text[], int num_args) {
  if (num_args > 1) {
    if (str_is_empty(text[1]) == 0)
      exit(0);
    error();
  } else {
    exit(0);
  }
}

void cmd_cd(char *text[], int num_args) {
  if (num_args > 2 || num_args < 2)
    error();
  else {
    if (str_is_empty(text[1]) == 0)
      error();
    chdir(text[1]);
  }
}

void identify_built_in_cmd(char *args[], int num_args) {

  if (strncmp(args[CMD_INDEX], "exit", 4) == 0)
    cmd_exit(args, num_args);
  else if (strncmp(args[CMD_INDEX], "echo", 4) == 0)
    cmd_echo(args, num_args);
  else if (strncmp(args[CMD_INDEX], "cd", 2) == 0)
    cmd_cd(args, num_args);
}

int split_arguments(char input[], char *args[]) {
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

  identify_built_in_cmd(arguments, argument_count);
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

    identify_built_in_cmd(arguments, argument_count);
  }
  fclose(fp);
}
