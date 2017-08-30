#include "header.h"

int loop() {
	int status;
	do {
		shell_prompt();
		char **args;
		args = read_parse();
		status = execute(args);
		free(args);
	} while (status);
	return 1;
}