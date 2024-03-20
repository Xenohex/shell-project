#ifndef COMMANDS_H
#define COMMANDS_H

#define DEFAULT_PATH "/bin/"

// exits the program with successful code
void cmd_exit(char **text, int num_args);
// chooses a new current working directory for the program
void cmd_cd(char **text, int num_args);
// chooses one or multiple possible paths to search for executables
void cmd_path(char **text, int num_args);

#endif
