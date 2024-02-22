#ifndef SHELL_H
#define SHELL_H

int split_arguments(char input[], char *args[]);
void interactive_mode();
void batch_mode(char filename[]);

void identify_built_in_cmd(char *args[], int num_args);
void cmd_exit(char *text[], int num_args);
void cmd_cd(char *text[], int num_args);

#endif
