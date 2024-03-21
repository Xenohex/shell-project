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
returns -2 if '>' IS found but the input is not valid
*/
int find_redirection(char **args, int num_args) {
  int r_index = -1;
  int redirection_found = 0;

  for (int i = 0; i < num_args; i++) {
    if (strchr(args[i], '>') != NULL) {
      if (redirection_found != 1) {
        // make sure only the first redirection is counted
        r_index = i;
        redirection_found = 1;
      } else {
        // if() block below will handle error
      }
    }
  }
  /*
  Tests for:
  * if last arg is '>'
  * first arg is '>'
  * if there is more than one argument after '>'
  */
  if ((r_index == num_args - 1 &&
       args[r_index][strlen(args[r_index]) - 1] == '>') ||
      r_index == 0 || (r_index > 0 && num_args - r_index > 1)) {
    error(NON_FATAL_ERROR); // if redirection operator is found but not valid
    return -2;
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

  char r_arg[MAX_CHARS]; // argument w/ redirection
  char r_arg_backwards[MAX_CHARS];
  strcpy(r_arg, args[r_index]);

  // ALONE
  if (strlen(r_arg) == 1) {
    condition = ALONE;
  } else { // look for before and/or after

    // AFTER
    // since strchr includes '>', must be greater than 1
    if (strlen(strchr(r_arg, '>')) > 1) {
      condition = AFTER;
      is_both++;
    }

    // BEFORE
    // since strchr includes '>', must be greater than 1
    strcpy(r_arg_backwards,
           args[r_index]);           // re-copy argument to new string
    reverse_string(r_arg_backwards); // reverse the string to check for text on
                                     // the other side of '>'
    if (strlen(strchr(r_arg_backwards, '>')) > 1) {
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

/*
Takes in original arguments, number of original arguments, index of redirection,
the type of redirection as defined by the RedirectionTextPosition enum, and the
string to move the output text to.
*/
int filter_redirection(char **args, int num_args, int r_index,
                       int redirection_type, char *redirect_str_ptr) {
  /*
  positions to check / do something about:
  * alone, after, before, both
  every type path needs to do three things:
  * copy output text to redirect_str_ptr
  * set args[r_index] to NULL
  * reduce num_args
  */
  switch (redirection_type) {
  case ALONE: // cmd arg > output
    if (num_args - r_index != 2)
      error(NON_FATAL_ERROR); // if there are more than 2 args after '>', or
                              // somehow only one argument
    else {
      strcpy(redirect_str_ptr, args[r_index + 1]);
      args[r_index] = NULL;
      num_args -= 2;
    }
    break; // END ALONE

  case AFTER: // cmd arg >output
    if (num_args - r_index != 1)
      // if there are more arguments after r_index
      error(NON_FATAL_ERROR);
    else {
      strcpy(redirect_str_ptr, args[r_index]);
      redirect_str_ptr++;
      args[r_index] = NULL;
      num_args -= 1;
    }
    break; // END AFTER

  case BEFORE: // cmd arg> output
    if (num_args - r_index != 2)
      // if there are more arguments after redirection target
      error(NON_FATAL_ERROR);
    else {
      args[r_index][strlen(args[r_index]) - 1] = '\0';
      strcpy(redirect_str_ptr, args[r_index + 1]);
      args[r_index + 1] = NULL;
      num_args -= 1;
    }
    break; // END BEFORE

  case BOTH: // cmd arg>output
    if (num_args - r_index != 1) {
      error(NON_FATAL_ERROR);
    } else {
      // output text
      strcpy(redirect_str_ptr, args[r_index]);
      redirect_str_ptr = strchr(redirect_str_ptr, '>');
      redirect_str_ptr++;
      // argument text
      reverse_string(args[r_index]);              // flip r_arg
      args[r_index] = strchr(args[r_index], '>'); // remove reversed output text
      args[r_index]++;                            // remove '>'
      reverse_string(args[r_index]);              // flip r_arg again
      // no need to set NULL; the number of arguments didn't change
    }
    break; // END BOTH

  default:
    // bad args
    error(NON_FATAL_ERROR);
  } // end switch

  // printf("final redirection target: %s\n", redirect_str_ptr);
  return num_args;
}

// redirects input text given to a text file of given name
void redirect(char text[], char filename[]) {
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
  // fprintf(fp, text);
  fclose(fp);
}
