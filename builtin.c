#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *lsh_pwd() {
	if (getcwd(home_dir, sizeof(home_dir)) != NULL) {
		return home_dir;
	}
	else {
		perror("getcwd() error");
	}
	return "";
}

int shell_cd(char *args[]) {
	if (args[1] == NULL || strcmp(args[1], " ") == 0 || strcmp(args[1], "") == 0 || strcmp(args[1], "~") == 0) {
		if (chdir(home_dir) != 0) {
			perror("Couldn't run cd command");
		}
	}
	else {
		char cd_dir[MAXN];
		int k = 0;
		for (int j = 0; j < strlen(args[1]); j++) {
			if (j == 0 && args[1][j] == '~') {
				strcpy(cd_dir, home_dir);
				k = strlen(home_dir);
			}
			else {
				cd_dir[k++] = args[1][j];
			}
		}
		cd_dir[k++] = '\0';
		printf("%s\n", cd_dir);
		if (chdir(cd_dir) != 0) {
			perror("Couldn't run cd command");
		}
		printf("%s\n", lsh_pwd());
	}
	return 1;
}

int shell_echo(char * args[]) 
{
	if (args[1]==NULL)
	{
		printf("\n");
		return 1;
	}
}
int shell_exit() {
	return 0;
}