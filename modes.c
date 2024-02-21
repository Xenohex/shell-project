#include "modes.h"

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "error.h"

#define MAX_CHAR_LIMIT 128
#define CMD_EXIT "exit "

void identify_cmd(char* cmd, char* args[], num_args) {
    if (strcmp(cmd, CMD_EXIT) == 0)
        cmd_exit(num_args);
    else if(strcmp(cmd, "echo ") == 0)
        cmd_echo(args, num_args);
    else if(strcmp(cmd, "cd ") == 0)
        cmd_cd(args, num_args);
}

int split_arguments(char input[], char* command, char* arguments) {
    char *sep_raw_input = strtok(input, " ");
    int argument_count = 0;

    for (int i = 0; sep_raw_input != NULL; i++) {
        if (i == 0) {
            command = sep_raw_input;
        }
        else {
            arguments[i] = sep_raw_input;
            sep_raw_input = strtok(NULL, " ");
        }
        argument_count++;
    }
    return argument_count;
}

void interactive_mode() {
    printf("wish> ");

    char input[MAX_CHAR_LIMIT];
    fgets(input, MAX_CHAR_LIMIT, stdin);

    /*if (strcmp(input, CMD_EXIT) == 0) { // if input == exit, exit
        cmd_exit();
    }*/

    //split up the string
    char* command;
    char *arguments[MAX_CHAR_LIMIT];
    int argument_count = split_arguments(input, command, arguments);

    identify_cmd(command, arguments, argument_count);
}

/*
void batch_mode(char filename[]) {
    FILE *fp;
    char line[MAX_CHAR_LIMIT];

    // opening file for reading
    fp = fopen(filename , "r");
    if (fp == NULL) {
        perror("Error opening file");
    }
    while (fgets(line, MAX_CHAR_LIMIT, fp) != NULL) {
        cmd_echo(line);
    }
    fclose(fp);
}
*/

