#ifndef SHARED_H
#define SHARED_H

#define MAX_ARGS 32
#define MAX_CHARS 128

// return 0 if string length < 2, return 1 otherwise
int str_is_empty(char *str);
// replaces all instances of the newline character with the NULL character
void remove_newline(char *text);
// split the given arguments into separate pieces
int split_arguments(char *input, char **args);
// reverses inputted string
void reverse_string(char *str);

//
// FUNCTIONS FOR TESTING PURPOSES ONLY GO HERE
//
void print_array_pointer(char **args, int num_args);
void print_array_array(char args[MAX_ARGS][MAX_CHARS], int num_args);

#endif
