#include "header.h"

int launch (char **args) {
	pid_t pid, wpid;
	int is_background = 0, i, status;
	pid = fork();
	for (i = 0; args[i] != NULL; i++) {
		if (strcmp(args[i], "&") == 0 && args[i+1] == NULL) {
			is_background = 1;
			args[i] = NULL;
			array_process[process_idx].pid = pid;
			strcpy(array_process[process_idx].name, args[0]);
			process_idx++;
		}
	}
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("Couldn't run the command");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		perror("Couldn't Fork");
	}
	else {
		if (is_background) {
			return 1;
		}
		else {
			do {
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	return 1;
}

int execute(char **args) {
	if (args[0] == NULL) {
		return 1;
	}
	if (strcmp(args[0], "cd") == 0) {
		printf("args[1]: %s\n", args[1]);
		cd(args);
	}
	else if (strcmp(args[0], "echo") == 0) {
		echo(args);
	}
	else if (strcmp(args[0], "pwd") == 0) {
		printf("%s\n", pwd());
	}
	else if (strcmp(args[0], "exit") == 0) {
		shell_exit();
	}
	else {
		return launch(args);
	}
}

int main() {
	int status;
	pwd();
	strcpy(home_dir, cur_dir);
	do {
		shell_prompt();
		char **args;
		args = read_parse();
		status = execute(args);
		free(args);
	} while (status);
	return 0;
}