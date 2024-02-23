#ifndef COMMANDS_H
#define COMMANDS_H

int str_is_empty(char *str);
void cmd_exit(char **text, int num_args);
void cmd_cd(char **text, int num_args);
void cmd_path(char **text, int num_args);
// void cmd_echo(char **text, int num_args);

#endif
