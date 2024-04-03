#ifndef SHELL_H
#define SHELL_H

#include "shared.h"
// ./wish with no arguments, runs until exited by user or fatal error
void interactive_mode();
// ./wish <filename>, interactive mode with predefined commands. runs until exit
// call or end of file
void batch_mode(char filename[]);
// return 0 if command is built in, 1 if not
int identify_built_in_cmd(char *args[MAX_CHARS], int num_args);
// if command cannot be found in internal files, search path for it
void execute_external_cmd(char *args[MAX_CHARS], int num_args);

#endif
