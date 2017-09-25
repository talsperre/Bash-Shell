#include "header.h"

/*
	Input: Signal Number
	Output: Returns if a child process has exited successfully or not
*/

void child_exit_handler (int sig) {
	int status, pos;
	pid_t wpid = waitpid(-1, &status, WNOHANG);
	if (wpid > 0 && WIFEXITED(status) == 0) {
		fprintf(stderr, "\nProcess with pid: %d exited normally\n", wpid);
	}
	if (wpid > 0 && WIFSIGNALED(status) == 0) {
		fprintf(stderr, "\nProcess with pid: %d exited with signal %d\n", wpid, sig);
	}
	for (pos = 1; pos < proc_idx; pos++) {
		if (array_process[pos].pid == wpid) {
			array_process[pos].is_null = 1;
		}
	}
}

/*
	Input: Signal Number
	Output: Checks for signals
*/

// ctrl-c
void ctrl_c_signal_handler (int sig) {
	printf("\nCaught signal %d\n", sig);
	if (is_foreground) {
		kill(foreground_pid, SIGINT);
	}
}

// ctrl-z
void ctrl_z_signal_handler (int sig) {
	printf("\nCaught signal %d\n", sig);
	if (is_foreground) {
		kill(foreground_pid, SIGTSTP);
		array_process[proc_idx].pid = foreground_pid;
		array_process[proc_idx].is_null = 0;
		proc_idx++;
	}
}

int next_input () {
	return 1;
}