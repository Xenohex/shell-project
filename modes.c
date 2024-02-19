#include "modes.h"

#include <stdio.h>
#include <string.h>
#include "echo.h"

#define MAX_CHAR_LIMIT 128
#define CMD_EXIT "exit\n"

loop_t interactive_mode(void) {
    printf("wish> ");

    char input[MAX_CHAR_LIMIT];
    fgets(input, MAX_CHAR_LIMIT, stdin);

    if (strcmp(input, CMD_EXIT) == 0) { // if input == exit, exit
        return exit;
    }
    
    cmd_echo(input);

    return active;
}

void batch_mode(char file[]) {
    FILE *fp;
    char line[MAX_CHAR_LIMIT];

    /* opening file for reading */
    fp = fopen(file , "r");
    if (fp == NULL) {
        perror("Error opening file");
    }
    while (fgets(line, MAX_CHAR_LIMIT, fp) != NULL) {
        cmd_echo(line);
    }
    fclose(fp);
}
