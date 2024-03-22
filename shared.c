#include "shared.h"

#include <stdio.h>
#include <string.h>

// What goes here?
// * anything shared between multiple other files
// * non-specific use functions

// return 0 if string length < 2, return 1 otherwise
int str_is_empty(char *str) {
  if (strlen(str) < 2)
    return 0;
  return 1;
}

// replaces all instances of the newline character with the NULL character
void remove_newline(char *text) {
  int length = strlen(text);
  for (int i = 0; i < length; i++) {
    if (text[i] == '\n') {
      text[i] = '\0';
    }
  }
  // int idx = 0;
  // while (text[idx] != '\0') {
  //   if (text[idx] == '\n') {
  //     text[idx] = '\0';
  //   }
  //   idx++;
  // }
}

// removes leading whitespace
void trim_white_space(char *str, char *trim_str) {
  int idx = 0, j, k = 0;

  // Iterate String until last
  // leading space character
  while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n') {
    idx++;
  }

  // Run a for loop from index until the original
  // string ends and copy the content of str to str1
  for (j = idx; str[j] != '\0'; j++) {
    trim_str[k] = str[j];
    k++;
  }

  // Insert a string terminating character
  // at the end of new string
  // trim_str[k] = '\0';
}

// split the given arguments into separate pieces
int split_arguments(char *input, char **args) {
  char *token = strtok(input, " ");
  int argument_count = 0;

  for (int i = 0; token != NULL; i++) {
    args[i] = token;
    token = strtok(NULL, " ");
    argument_count++;
  }
  args[argument_count] = NULL;
  return argument_count;
}

// reverses inputted string
void reverse_string(char *str) {
  int len = strlen(str);
  for (int i = 0, j = len - 1; i <= j; i++, j--) {
    // swapping characters
    char c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

//
// FUNCTIONS FOR TESTING PURPOSES ONLY GO HERE
// These should all probably get removed once the program is finished
//
void print_array_pointer(char **args, int num_args) { // REMOVE
  printf("array: ");
  for (int i = 0; i < num_args; i++) {
    printf("%s ", args[i]);
  }
  puts("");
}

void print_array_array(char args[MAX_ARGS][MAX_CHARS], int num_args) { // REMOVE
  printf("array: ");
  for (int i = 0; i < num_args; i++) {
    printf("%s ", args[i]);
  }
  puts("");
}
