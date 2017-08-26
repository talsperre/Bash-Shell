#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char inp_string[1024];
char ** array_tokens;

int main() {
	scanf("%1024[^\n]",inp_string);
    array_tokens = malloc(1024 * sizeof(char*));
	
	char delim[2] = " \t";
	
	char *token;

	/* get the first token */
	token = strtok(inp_string, delim);

	int size = 0, i;
	
	/* walk through other tokens */
	while (token != NULL ) {
	    array_tokens[size++]=token;
	    token = strtok(NULL, s);
	}

	for (i = 0; i < size; i++) {
		printf("%s\n",array_tokens[i]);
	}
}