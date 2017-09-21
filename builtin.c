#include "header.h"

/*
	Returns the current working directory
	Also updates the value of cur_dir (A global string)
*/

char *pwd() {
	if (getcwd(cur_dir, sizeof(cur_dir)) != NULL) {
		return cur_dir;
	}
	else {
		perror("getcwd() error");
	}
	return "";
}

/*
	Input: An array of tokens
	Output: Changes the working directory based on input
*/

int cd(char *args[]) {
	if (args[1] == NULL || strcmp(args[1], "~") == 0) {
		if (chdir(home_dir) != 0) {
			perror("Couldn't run cd command");
		}
	}
	else {
		int k = 0, j;
		char cd_dir[MAXN];
		for (j = 0; j < strlen(args[1]); j++) {
			if (j == 0 && args[1][j] == '~') {
				strcpy(cd_dir, home_dir);
				k = strlen(home_dir);
			}
			else {
				cd_dir[k++] = args[1][j];
			}
		}
		cd_dir[k] = '\0';
		if (chdir(cd_dir) != 0) {
			perror("Couldn't run cd command");
		}
	}
	return 1;
}

/*
	Input: An array of tokens
	Output: Outputs the text on the shell
*/

int echo (char * args[]) {
	if (args[1] == NULL) {
		printf("\n");
		return 1;
	}
	else {
		int i;
		for (i = 1; args[i] != NULL; i++) {
			printf("%s ", args[i]);
		}
		printf("\n");
	}
	return 1;
}

/*
	Exits from the shell.
*/

int shell_exit() {
	exit(EXIT_SUCCESS);
	return 0;
}