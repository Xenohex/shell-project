#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

// return 0 if string length < 2, return 1 otherwise
int str_is_empty(char *str) {
  if (strlen(str) < 2)
    return 0;
  return 1;
}

void cmd_echo(char *text[], int num_args) {
  // todo make this take in all arguments except the "echo" command
  for (int i = 1; i < num_args; i++) {
    printf("%s", text[i]);
    if (i != (num_args - 1))
      printf(" ");
  }
}
