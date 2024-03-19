#ifndef COMMANDS_H
#define COMMANDS_H

#define DEFAULT_PATH "/bin/"
#define MAX_ARGS 32
#define MAX_CHARS 128

int str_is_empty(char *str);
void cmd_exit(char **text, int num_args);
void cmd_cd(char **text, int num_args);
void cmd_path(char **text, int num_args);

#endif
