#include "header.h"



int main() {
	int status;
	pwd();
	proc_idx = 1;
	curr_pid=getpid();
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