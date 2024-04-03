#ifndef PARALLEL_H
#define PARALLEL_H

#include "shared.h"
/*
Returns:
-1 if no parallels,
number of parallels otherwise
*/
int find_parallels(char args[MAX_CHARS], char *cmd_strs[MAX_CHARS]);

// separates input strings into separated arguments and keeps them in an array
void separate_parallels(char *cmd_strs[MAX_CHARS], int cmd_strs_count,
                        char *cmds[MAX_ARGS][MAX_CHARS], int *cmd_lengths);

// calls execute_external_cmd from shell files using arg_struct
void *call_external(void *arguments);

// executes commands in parallel on different threads
void execute_parallel(char *commands[MAX_ARGS][MAX_CHARS],
                      int commands_num_args[MAX_ARGS], int command_count);

/* returns 0 if parallel found and run, -1 otherwise.
basically completes the whole input to parallelization sequence */
int try_parallel(char args[MAX_CHARS]);

#endif
