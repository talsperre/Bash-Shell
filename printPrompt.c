#include "header.h"

char *get_user_name() {
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw) {
		return pw->pw_name;
	}
	return "";
}

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

int shell_prompt () {
	int check = gethostname(hostname, HOST_NAME_MAX);
	if (check) {
		perror("gethostname");
		return EXIT_FAILURE;
	}
	printf("%s@%s:%s$ ", get_user_name(), hostname, print_dir(pwd()));
	return 1;
}