#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXN 1234
char home_dir[MAXN];

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
	if (args[1] == NULL || strcmp(args[1], "~") == 0) {
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

int main () {
	char *ar[] = {"cd", "~/Inception/"};
	printf("pwd: %s\n", lsh_pwd());
	shell_cd(ar);
	return 0;
}