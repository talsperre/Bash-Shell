#include "header.h"

/*
	Input: Array of tokens
	Responsible for launching the processes. 
	Checks for '&':
	If it exists => Opens the process in background
	Else =>	Opens the process in foreground
	Supports signal handling
*/

int launch (char **args) {
	pid_t pid, wpid;
	int is_background = 0, i, status;
	pid = fork();
	for (i = 0; args[i] != NULL; i++) {
		if (strcmp(args[i], "&") == 0 && args[i+1] == NULL) {
			signal(SIGCHLD, child_exit_handler);
			is_background = 1;
			args[i] = NULL;
			array_process[proc_idx].pid = pid;
			strcpy(array_process[proc_idx].name, args[0]);
			array_process[proc_idx].is_null = 0;
			proc_idx++;
		}
	}
	if (pid == 0) {
		args = redirection(args);
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

/*
	Input: An array of tokens
	Output: Executes the required process by calling system built-ins or
	by calling the launch function
*/

int execute(char **args) {
	
	if (args[0] == NULL) {
		return 1;
	}
	int cnt = 0, cnt1 = 0, i, is_redirection;
	
	for (i =0; args[i] != NULL; i++) {
		if (strcmp(args[i], "|") == 0) {
			cnt++;
		}
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], ">>") == 0) {
			cnt1++;
		}
	}
	if ( cnt != 0) {
		pipeHandler(args);
	}
	else if (strcmp(args[0], "cd") == 0) {
		cd(args);
	}
	else if (strcmp(args[0], "echo") == 0 && cnt1 == 0) {
		echo(args);
	}
	else if (strcmp(args[0], "pwd") == 0) {
		printf("%s\n", pwd());
	}
	else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
		shell_exit();
	}
	else if (strcmp(args[0], "ls") == 0 && cnt1 == 0) {
		ls(args);
	}
	else if (strcmp(args[0], "pinfo") == 0) {
		pinfo(args);
	}
	else if (strcmp(args[0], "nightswatch") == 0) {
		nightswatch(atoi(args[2]));
	}
	else if (strcmp(args[0], "setenv") == 0) {
		shell_setenv(args);
	}
	else if (strcmp(args[0], "unsetenv") == 0) {
		shell_unsetenv(args);
	}
	else if (strcmp(args[0], "jobs") == 0) {
		jobs(args);
	}
	else if (strcmp(args[0], "kjob") == 0) {
		kjob(args);
	}
	else if (strcmp(args[0], "overkill") == 0) {
		overkill(args);
	}
	else if (strcmp(args[0], "fg") == 0) {
		fg(args);
	}
	else if (strcmp(args[0], "bg") == 0) {
		bg(args);
	}
	else {
		return launch(args);
	}
}