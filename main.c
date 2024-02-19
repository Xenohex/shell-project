#include <stdio.h>

#include "echo.h"
#include "modes.h"

#define NO_ARGUMENTS 1

int main(int argc, char* argv[]) {
    if (argc == NO_ARGUMENTS) {
        while(interactive_mode() == active);
    }
    else if (argc > NO_ARGUMENTS) {
        batch_mode(argv[1]);
    }

    return 0;
}