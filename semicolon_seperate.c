#include "header.h"

char ** semicolon_parse() {
	int pos = 0;
	char *inp_string = NULL, *token;
	ssize_t bufsize = 0;
	getline(&inp_string, &bufsize, stdin);
	char **tokens = malloc(bufsize * sizeof(char*));

	if (!tokens) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(inp_string, ";");
	while (token != NULL) {
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, ";");
	}
	tokens[pos] = NULL;
	return tokens;	
}