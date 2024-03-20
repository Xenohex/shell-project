#include "redirection.h"

#include <stdio.h> // REMOVE?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "shared.h"

/*
returns index of argument where redirection operator is located
returns -1 if '>' is not found
*/
int find_redirection(char **args, int num_args) {
  char *redirection;
  int r_index = -1;
  int redirection_found = 0;

  for (int i = 0; i < num_args; i++) {
    if (strchr(args[i], '>') != NULL) {
      if (redirection_found == 1) {
        error(NON_FATAL_ERROR);
        break;
      }
      r_index = i;
      redirection_found = 1;
    }
  }
  if (r_index == num_args - 1 &&
      args[r_index][strlen(args[r_index]) - 1] == '>') {
    error(NON_FATAL_ERROR); // if redirection operator is the last (or only)
                            // character in the last argument
  }

  return r_index;
}

/*
Finds and returns the type of redirection
0/ALONE, 1/AFTER, 2/BEFORE, 3/BOTH
*/
int find_redirection_type(char **args, int num_args, int r_index) {
  /*
  if > is alone
  if > has one argument after
  if > has one argument before
  if > has arguments before AND after
  */
  int is_both = 0;
  int condition = -1;

  char *r_arg; // argument w/ redirection
  char *r_arg_backwards;
  strcpy(r_arg, args[r_index]);

  // ALONE
  if (strlen(r_arg) == 1) {
    condition = ALONE;
    puts("r_condition: ALONE");
  } else { // look for before and/or after

    // AFTER
    // since strchr includes '>', must be greater than 1
    if (strlen(strchr(r_arg, '>')) > 1) {
      condition = AFTER;
      puts("r_condition: AFTER");
      is_both++;
    }

    // BEFORE
    // since strchr includes '>', must be greater than 1
    strcpy(r_arg_backwards, args[r_index]); // re-copy argument to new string
    reverse_string(r_arg_backwards); // reverse the string to check for text on
                                     // the other side of '>'
    if (strlen(strchr(r_arg_backwards, '>')) > 1) {
      condition = BEFORE;
      puts("r_condition: BEFORE");
      is_both++;
    }

    // BOTH
    if (is_both == 2) {
      condition = BOTH;
      puts("r_condition: BOTH");
    }
  }
  return condition;
}

// redirects input text given to a text file of given name
void redirect(char **args, int num_args,
              char filename[]) { // todo make this
  /*
  in the external command function, the parent should open a pipe, give it to
  the child to write to, and once it is does writing (command finishes running
  and outputting), the function should feed the result of that pipe to THIS
  function to finally write it to a real file.
  */
  FILE *fp;
  char line[MAX_CHARS];

  if (access(filename, F_OK) != 0)
    truncate(filename, 0); // deletes everything in the file

  // opening file for reading
  fp = fopen(filename, "w");
  if (fp == NULL) {
    error(NON_FATAL_ERROR);
  }
  while (fgets(line, MAX_CHARS, fp) != NULL) {
    // print to file
  }
  fclose(fp);
}
