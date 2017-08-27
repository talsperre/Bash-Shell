#include "header.h"

int read_parse() {
	scanf("%1024[^\n]",inp_string);
    array_tokens = malloc(1024 * sizeof(char*));
	
	char delim[2] = " \t";
	
	char *token;

	/* get the first token */
	token = strtok(inp_string, delim);

	int i;
	
	/* walk through other tokens */
	while (token != NULL ) {
	    array_tokens[array_token_size++]=token;
	    token = strtok(NULL,delim);
	}
	array_tokens[array_token_size++] = NULL;
}