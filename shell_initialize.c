#include "header.h"

/*
	Called once by the main function
	Initilaizes the shell with the home directory, signal handling &
	process id
*/

int initialize() {
	is_foreground = 0;
	signal(SIGINT, ctrl_c_signal_handler);
	signal(SIGTSTP, ctrl_z_signal_handler);
	pwd();
	proc_idx = 1;
	curr_pid=getpid();
	strcpy(home_dir, cur_dir);
}