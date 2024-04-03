#ifndef PARALLEL_H
#define PARALLEL_H

#include "shared.h"
/*
Returns:
-1 if no parallels
number of parallels otherwise

p_list parameter stores list of all parallels
*/
int find_parallel(char args[MAX_CHARS], char *cmd_strs[MAX_CHARS]);
/*
Finds and returns the types of redirection in array
0/ALONE, 1/AFTER, 2/BEFORE, 3/BOTH
*/
void find_parallel_types(char *args[MAX_CHARS], int num_args, int *p_list,
                         int p_num, int *p_conditions);
/*
Takes in original arguments, number of original arguments, indeces of parallels,
the types of parallels as defined by the TextPosition enum, and
a 3 dimensional array to store command arguments to
*/
int filter_parallel(char *args[MAX_CHARS], int num_args, int *p_list, int p_num,
                    int *p_types, char commands[MAX_ARGS][MAX_ARGS][MAX_CHARS],
                    int commands_num_args[MAX_ARGS]);

/*
Actually executes commands in parallel. Last step in the process.
Takes in an array of commands consisting of separated arguments, and
* the number of arguments of all the commands it contains.
*/
void execute_parallel(char *commands[MAX_ARGS][MAX_CHARS],
                      int commands_num_args[MAX_ARGS]);

// returns 0 if parallel found and run, -1 otherwise
int try_parallel(char args[MAX_CHARS]);

#endif
