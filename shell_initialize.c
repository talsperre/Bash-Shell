#include "header.h"

int initialize() {
	signal(SIGINT, signal_handler);
	pwd();
	proc_idx = 1;
	curr_pid=getpid();
	strcpy(home_dir, cur_dir);
}