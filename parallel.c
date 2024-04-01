#include <stdio.h> // REMOVE?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shared.h"

/*
Plan of attack:
* Identify
* separate
* execute (in parallel)
*/

/*
Returns:
-1 if no parallels
0 if there are parallels

p_list parameter stores list of all parallels
*/
int find_parallel(char **args, int num_args, int *p_list) {
  int p_index_list[num_args];
  int p_list_counter = 0;
  int parallel_found = -1;

  for (int i = 0; i < num_args; i++) {
    if (strchr(args[i], '&') != NULL) {
      p_index_list[p_list_counter] = i;
      parallel_found = 0;
      p_list_counter++;
    }
  }
  return parallel_found;
}

/*
Finds and returns the types of redirection in array
0/ALONE, 1/AFTER, 2/BEFORE, 3/BOTH
*/
int find_parallel_types(char **args, int num_args, int r_index) {
  /*
  if > is alone
  if > has one argument after
  if > has one argument before
  if > has arguments before AND after
  */
  int is_both = 0;
  int condition = -1;

  char r_arg[MAX_CHARS]; // argument w/ redirection
  char r_arg_backwards[MAX_CHARS];
  strcpy(r_arg, args[r_index]);

  // ALONE
  if (strlen(r_arg) == 1) {
    condition = ALONE;
  } else { // look for before and/or after

    // AFTER
    // since strchr includes '>', must be greater than 1
    if (strlen(strchr(r_arg, '&')) > 1) {
      condition = AFTER;
      is_both++;
    }

    // BEFORE
    // since strchr includes '>', must be greater than 1
    strcpy(r_arg_backwards,
           args[r_index]);           // re-copy argument to new string
    reverse_string(r_arg_backwards); // reverse the string to check for text on
                                     // the other side of '>'
    if (strlen(strchr(r_arg_backwards, '&')) > 1) {
      condition = BEFORE;
      is_both++;
    }

    // BOTH
    if (is_both == 2) {
      condition = BOTH;
    }
  }
  return condition;
}

void execute_parallel(char **args, int num_args, int *p_list) {}
