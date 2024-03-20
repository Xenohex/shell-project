#ifndef REDIRECTION_H
#define REDIRECTION_H

// possible positions of text around '>'
enum Condition { ALONE, AFTER, BEFORE, BOTH };
/*
returns index of argument where redirection operator is located
returns -1 if '>' is not found
 */
int find_redirection(char **args, int num_args);
/*
Finds and returns the type of redirection
0/ALONE, 1/AFTER, 2/BEFORE, 3/BOTH
*/
int find_redirection_type(char **args, int num_args, int r_index);
// changes the arguments to remove the redirection operator
void filter_redirection(char **args, int num_args, int r_index);
// redirects input text given to a text file of given name
void redirect(char **args, int num_args, char filename[]);

#endif
