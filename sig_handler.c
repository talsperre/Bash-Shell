#include "header.h"

void child_exit_handler (int sig) {
	int status;
	pid_t wpid = waitpid(-1, &status, WNOHANG);
	if (wpid > 0 && WIFEXITED(status) == 0) {
		fprintf(stderr, "\nProcess with pid: %d exited normally\n", wpid);
		next_input();
	}
	if (wpid > 0 && WIFSIGNALED(status) == 0) {
		fprintf(stderr, "\nProcess with pid: %d exited with signal %d\n", wpid, sig);
		next_input();
	}
}

void signal_handler (int sig) {
	printf("\nCaught signal %d, Exiting...\n", sig);
	exit(1);
}

int next_input () {
	loop();
}