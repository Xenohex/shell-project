#ifndef MODES_H
#define MODES_H

typedef enum {active, exit} loop_t;

loop_t interactive_mode(void);
void batch_mode(char file[]);

#endif