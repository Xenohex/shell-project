#include <stdio.h> // REMOVE?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "parallel.h"
#include "shared.h"
#include "shell.h"

/*
Returns:
-1 if no parallels,
number of parallels otherwise
*/
int find_parallels(char args[MAX_CHARS], char *cmd_strs[MAX_CHARS]) {
  int parallels = split_arguments(args, cmd_strs, "&");

  if (parallels > 1)
    return parallels;
  else
    return -1;
}

// separates input strings into separated arguments and keeps them in an array
void separate_parallels(char *cmd_strs[MAX_CHARS], int cmd_strs_count,
                        char *cmds[MAX_ARGS][MAX_CHARS], int *cmd_lengths) {
  for (int i = 0; i < cmd_strs_count; i++) {
    cmd_lengths[i] = split_arguments(cmd_strs[i], cmds[i], " ");
  }
}

// struct to submit arguments to threaded function
struct arg_struct {
  char *args[MAX_CHARS];
  int num_args;
};

// calls execute_external_cmd from shell files using arg_struct
void *call_external(void *arguments) {
  struct arg_struct *args = arguments;

  if (args->num_args > 0)
    execute_external_cmd(args->args, args->num_args);
  return NULL;
}

// executes commands in parallel on different threads
void execute_parallel(char *commands[MAX_ARGS][MAX_CHARS],
                      int commands_num_args[MAX_ARGS], int command_count) {

  int parallel_rcs[command_count];
  struct arg_struct args;

  for (int i = 0; i < command_count; i++) {
    copy_char_array(args.args, commands[i], commands_num_args[i]);
    args.num_args = commands_num_args[i];

    parallel_rcs[i] = fork();
    if (parallel_rcs[i] < 0)
      error(FATAL_ERROR);
    else if (parallel_rcs[i] == 0) {
      call_external(&args);
      exit(0);
    }
  }
  for (int i = 0; i < command_count; i++)
    wait(NULL);
}

/* returns 0 if parallel found and run, -1 otherwise.
basically completes the whole input to parallelization sequence */
int try_parallel(char args[MAX_CHARS]) {
  char *command_strs[MAX_CHARS];
  char *commands[MAX_ARGS][MAX_CHARS];
  int commands_num_args[MAX_ARGS] = {0};
  // checks if parallel exists
  if (strcmp(args, "&") == 0) // check to make sure there isn't just a single &
    return 0;
  int cmd_count = find_parallels(args, command_strs);
  if (cmd_count == -1)
    return -1;
  else if (cmd_count == 1 && commands_num_args[0] == 0)
    return 0;
  else {
    separate_parallels(command_strs, cmd_count, commands, commands_num_args);
    execute_parallel(commands, commands_num_args, cmd_count);
  }
  return 0;
}
