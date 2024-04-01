#include "shell.h"

#include <stdio.h> // REMOVE?
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "error.h"
#include "redirection.h"
#include "shared.h"

#define CMD_INDEX 0

extern char path[MAX_ARGS][MAX_CHARS];
extern int path_count;

// return 0 if command is built in, 1 if not
int identify_built_in_cmd(char **args, int num_args) {

  if (strncmp(args[CMD_INDEX], "exit", 4) == 0) {
    cmd_exit(args, num_args);
    return 0; // built-in command found
  } else if (strncmp(args[CMD_INDEX], "path", 4) == 0) {
    cmd_path(args, num_args);
    return 0; // built-in command found
  } else if (strncmp(args[CMD_INDEX], "cd", 2) == 0) {
    cmd_cd(args, num_args);
    return 0; // built-in command found
  }
  return 1; // command is not built-in
}

// if command cannot be found in internal files, search path for it
void execute_external_cmd(char **args, int num_args) {

  char output_file[MAX_CHARS] = "";
  char *output_file_p = output_file;
  int do_execute = 1;  // executes command if set to 1
  int do_redirect = 0; // redirects if set to 1

  int r_index = -1;
  r_index = find_redirection(args, num_args);
  if (r_index > 0) { // redirection location found and valid

    int r_type = find_redirection_type(args, num_args, r_index);
    num_args =
        filter_redirection(args, num_args, r_index, r_type, output_file_p);
    do_redirect = 1;

  } else if (r_index == -2) {
    do_execute = -1; // redirection error that causes impossible command
  }
  // print_array_pointer(args, num_args);

  int cmd_found = 0; // if cmd_found is set to 1, the command is found

  // loop through all paths
  if (do_execute == 1) {
    for (int path_counter = 0; path_counter < path_count && cmd_found != 1;
         path_counter++) {

      // create the target path
      char fullpath[MAX_CHARS];
      strcpy(fullpath, path[path_counter]);

      // create a copy of args[0]
      char cmd[MAX_CHARS];
      strcpy(cmd, args[0]);

      // concatenate path
      strcpy(cmd, strcat(fullpath, cmd));

      //  check if accesss to command exists, if so, execute it
      if (access(cmd, X_OK) == 0) {
        // access granted
        cmd_found = 1; // ensures the loop won't check any more paths

        char output_text[4096];
        int link[2]; // for piping/redirection

        if (do_redirect == 1)
          if (pipe(link) < 0) {
            error(FATAL_ERROR);
            // error_test(FATAL_ERROR, "ext_cmd: pipe failed");
          }
        int rc = fork();

        if (rc < 0) {
          // fork failed; exit
          error(FATAL_ERROR);
          // error_test(FATAL_ERROR, "ext_cmd: fork failed");
        } else if (rc == 0) {
          // child (new process)
          if (do_redirect == 1) {
            dup2(link[1], STDOUT_FILENO);
            close(link[0]);
            close(link[1]);
          }
          execv(cmd, args);
        } else {
          // parent goes down this path (original process)
          close(link[1]);
          if (do_redirect == 1) {
            int nbytes = read(link[0], output_text, sizeof(output_text));
            redirect(output_text, nbytes, output_file);
          }
          wait(NULL);
        }
      } else { // access fails
        if (path_counter == (path_count - 1)) {
          error(NON_FATAL_ERROR); // if there are multiple paths, only
                                  // errors if it never finds command
                                  // through any of the given paths
          // error_test(FATAL_ERROR, "ext_cmd: no cmd found");
        }
      }
    } // end loop
  }   // end if(execute == 0)
}

// ./wish with no arguments, runs until exited by user or fatal error
void interactive_mode() {
  printf("wish> ");

  char input[MAX_CHARS];
  fgets(input, MAX_CHARS, stdin);

  remove_newline(input);

  // split up the string
  char *arguments[MAX_CHARS];
  int argument_count = split_arguments(input, arguments);

  // arguments[0] = remove_newline(arguments[0]);

  if (argument_count > 0)
    if (identify_built_in_cmd(arguments, argument_count) == 1)
      execute_external_cmd(arguments, argument_count);
}

// ./wish <filename>, interactive mode with predefined commands. runs until
// exit call or end of file
void batch_mode(char filename[]) {
  FILE *fp;
  char line[MAX_CHARS];

  if (access(filename, R_OK) == 0) {

    // opening file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
      perror("Error opening file");
    }

    char trim_str[MAX_CHARS];
    while (fgets(line, MAX_CHARS, fp) != NULL) {

      // trim_white_space(line, trim_str);
      remove_newline(line);
      // printf("trim_str: %s", trim_str);

      // split up the string
      char *arguments[MAX_CHARS];
      int argument_count = split_arguments(line, arguments);

      if (argument_count > 0)
        if (identify_built_in_cmd(arguments, argument_count) == 1)
          execute_external_cmd(arguments, argument_count);
    }
    fclose(fp);

  } else {
    error(FATAL_ERROR); // bad batch file
  }
}
