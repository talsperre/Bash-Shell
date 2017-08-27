#include "header.h"

char *pwd() {
	if (getcwd(home_dir, sizeof(home_dir)) != NULL) {
		return home_dir;
	}
	else {
		perror("getcwd() error");
	}
	return "";
}

int cd(char *args[]) {
	if (args[1] == NULL || strcmp(args[1], " ") == 0 || strcmp(args[1], "") == 0 || strcmp(args[1], "~") == 0) {
		if (chdir(home_dir) != 0) {
			perror("Couldn't run cd command");
		}
	}
	else {
		
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
		printf("%s\n", pwd());
	}
	return 1;
}

int echo (char * args[]) {
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
