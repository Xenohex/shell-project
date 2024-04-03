#ifndef COMMANDS_H
#define COMMANDS_H

#define DEFAULT_PATH "/bin/"

#include "shared.h"

// exits the program with successful code
void cmd_exit(char *args[MAX_CHARS], int num_args);
// chooses a new current working directory for the program
void cmd_cd(char *args[MAX_CHARS], int num_args);
// chooses one or multiple possible paths to search for executables
void cmd_path(char *args[MAX_CHARS], int num_args);

#endif
