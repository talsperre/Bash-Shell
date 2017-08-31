#include "header.h"

/*
	An infinte loop which keeps taking input from the user until
	user exits the program
*/

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