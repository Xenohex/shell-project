#ifndef ERROR_H
#define ERROR_H

#define NON_FATAL_ERROR 0
#define FATAL_ERROR 1

// prints an error message if error code is non-fatal.
// otherwise, ends the program
void error(int code);
void error_test(int code, char msg[]);

#endif
