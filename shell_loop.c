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
		args = semicolon_parse();
		int i, j;
		for (i = 0; args[i] != NULL; i++) {
			char **argsi;
			argsi = read_parse(args[i]);
			status = execute(argsi);
			if (!status) {
				break;
			}
			free(argsi);
		}
		free(args);
	} while (status);
	return 1;
}