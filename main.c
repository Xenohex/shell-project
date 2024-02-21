#include <stdio.h>

#include "modes.h"

#define NO_ARGUMENTS 1

int main(int argc, char* argv[]) {
	while (argc == NO_ARGUMENTS)
		interactive_mode();
	if (argc > NO_ARGUMENTS) {
		batch_mode(argv[1]);
	}

	return 0;
}
