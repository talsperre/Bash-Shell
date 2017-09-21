#include "header.h"

/* Function:
	Reads and parses the input taken from the shell
	Input: void
	Output: array of pointers to individual components
*/

char ** read_parse(char *inp) {
	int pos = 0;
	char *token;
	ssize_t bufsize = 12345;
	char **tokens = malloc(bufsize * sizeof(char*));

	if (!tokens) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(inp, DELIM);
	while (token != NULL) {
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, DELIM);
	}
	tokens[pos] = NULL;
	return tokens;
}