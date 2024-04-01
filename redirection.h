#ifndef REDIRECTION_H
#define REDIRECTION_H

/*
returns index of argument where redirection operator is located
returns -1 if '>' is not found
returns -2 if '>' IS found but the input is not valid
*/
int find_redirection(char **args, int num_args);
/*
Finds and returns the type of redirection
0/ALONE, 1/AFTER, 2/BEFORE, 3/BOTH
*/
int find_redirection_type(char **args, int num_args, int r_index);
/*
Takes in original arguments, number of original arguments, index of redirection,
the type of redirection as defined by the RedirectionTextPosition enum, and the
string to move the output text to. Returns new num_args;
*/
int filter_redirection(char **args, int num_args, int r_index,
                       int redirection_type, char *redirect_str_ptr);
// redirects input text given to a text file of given name
void redirect(char text[], int nbytes, char filename[]);

#endif
