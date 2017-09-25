#include "header.h"

char **redirection (char **args) {
	int flag[5], i;
	char in_file[MAXN], out_file[MAXN], append_file[MAXN];
	for (i = 0; i < 5; i++) flag[i] = 0;
	for (i = 0; args[i] != NULL; i++) {
		if (strcmp(args[i], "<") == 0) {
			strcpy(in_file, args[i+1]);
			args[i] = NULL;
			flag[0] = 1;
		}
		else if (strcmp(args[i], ">>") == 0) {
			strcpy(append_file, args[i+1]);
			args[i] = NULL; 
			flag[1] = 1;
		}
		else if (strcmp(args[i], ">") == 0) {
			strcpy(out_file, args[i+1]);
			args[i] = NULL; 
			flag[2] = 1;
		}
	}
	
	if (flag[0]) {
		int fd = open(in_file, O_RDONLY);
		if (fd < 0) {
			fprintf(stderr, "Failed to open file \"%s\"\n", in_file);
			exit(0);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (flag[1]) {
		int fd = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0) {
			fprintf(stderr, "Failed to open file \"%s\"\n", append_file);
			exit(0);
		}
		dup2(fd, 1);
		close(fd);
	}
	if (flag[2]) {
		int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0) {
			fprintf(stderr, "Failed to open file \"%s\"\n", out_file);
			exit(0);
		}
		dup2(fd, 1);
		close(fd);
	}
	return args;
}