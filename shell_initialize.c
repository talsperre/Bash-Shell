#include "header.h"

/*
	Called once by the main function
	Initilaizes the shell with the home directory, signal handling &
	process id
*/

int initialize() {
	signal(SIGINT, signal_handler);
	pwd();
	proc_idx = 1;
	curr_pid=getpid();
	strcpy(home_dir, cur_dir);
}