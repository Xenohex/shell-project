#ifndef COMMANDS_H
#define COMMANDS_H

#define DEFAULT_PATH "/bin/"

int str_is_empty(char *str);
void cmd_exit(char **text, int num_args);
void cmd_cd(char **text, int num_args);
void cmd_path(char **text, int num_args);
char *return_path();
// void cmd_echo(char **text, int num_args);

#endif
