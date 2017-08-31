#include "header.h"

/*
	Returns the username of the user executing the shell
*/

char *get_user_name() {
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw) {
		return pw->pw_name;
	}
	return "";
}

/*
	Input: A string consisting of current directory name
	Output: Replaces '~' with the absolute path of the 
	home (Directory where shell ir run)
*/

char *print_dir(char cur_dir[]) {
	if (strstr(cur_dir, home_dir) != NULL) {
		int i = strlen(home_dir), j = 0;
		res[j++] = '~';
		for (; i < strlen(cur_dir); i++) {
			res[j++] = cur_dir[i];
		}
		res[j++] = '\0';
		return res;
	}
	else {
		return cur_dir;
	}
}

/*
	Prints the main prompt of the shell in the infinte loop
*/

int shell_prompt () {
	int check = gethostname(hostname, HOST_NAME_MAX);
	if (check) {
		perror("gethostname");
		return EXIT_FAILURE;
	}
	printf("%s@%s:%s$ ", get_user_name(), hostname, print_dir(pwd()));
	return 1;
}