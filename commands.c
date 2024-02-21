#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

void cmd_exit(int num_args) {
    if (args > 1) {
        error();
    }
    else {
        exit(0);
    }
}

void cmd_echo(char* text[], int num_args) {
    //todo make this take in all arguments except the "echo" command
    for (int i = 1; i < args; i++) {
        printf("%s", text[i]);
    }
    printf("\n");
}

void cmd_cd(char* text[], int num_args) {
    printf("you just tried to use cd\n");
}
