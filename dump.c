int launch (char **args) {
	pid_t pid, wpid;
	int is_background = 0;
	int status;
	pid = fork();
	/*if (strcmp(args[array_token_size-1], "&") == 0) {
		is_background = 1;
		args[array_token_size-1] = NULL;
		array_process[process_idx].pid = pid;
		strcpy(array_process[process_idx].name, args[0]);
	}*/
	//printf("pid: %d, is_background: %d\n", pid, is_background);
	if (pid == 0) {
		//printf("Hello Kanay\n");
		int i;
		//if ( args[0] == NULL)
		/*printf("args[0]: %s\n", args[0]);
		for (i = 0; args[i] != NULL; i++) {
			printf("%s\n", args[i]);
		}*/
		if (execvp(args[0], args) == -1) {
			perror("Couldn't run the command");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		perror("Couldn't Fork");
	}
	else {
		/*if (is_background) {
			int a = 0;
		}
		else {*/
			do {
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		//}
	}
	return 1;
}