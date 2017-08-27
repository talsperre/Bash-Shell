#include "header.h"

/*int read_parse() {
	char tmp;
	scanf("%c%1024[^\n]", &tmp, inp_string);
    array_tokens = malloc(1024 * sizeof(char*));
	
	char delim[2] = " \t";
	
	char *token;

	token = strtok(inp_string, delim);

	int i;
	while (token != NULL ) {
	    array_tokens[array_token_size++]=token;
	    token = strtok(NULL,delim);
	}
	array_tokens[array_token_size] = NULL;
	return 1;
}*/

char ** read_parse() {
	char *inp_string = NULL;
	ssize_t bufsize = 0;
	getline(&inp_string, &bufsize, stdin);
	int pos = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;
	if (!tokens) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(inp_string, DELIM);
	while (token != NULL) {
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, DELIM);
	}
	tokens[pos] = NULL;
	return tokens;
}