#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int shell_echo (char * args[]) {
	if (args[1]==NULL) {
		printf("\n");
		return 1;
	}
	else {
		int i;
		for (i = 1; args[i] != NULL; i++) {
			printf("%s ", args[i]);
		}
	}
	return 1;
}

int main() {
	char * arr[]={"echo","a","b","c","d", NULL};
	shell_echo(arr);
}