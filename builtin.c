#include "header.h"

char *pwd() {
	if (getcwd(cur_dir, sizeof(cur_dir)) != NULL) {
		return cur_dir;
	}
	else {
		perror("getcwd() error");
	}
	return "";
}

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

int shell_exit() {
	return 0;
}