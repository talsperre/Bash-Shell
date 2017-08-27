#include "header.h"

typedef struct process {
	pid_t pid;
	char name[MAXN];
} proc;

proc array_process[MAXN];

int launch() {
	pid_t pid, wpid;
	int status;
}

/*int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  return lsh_launch(args);
}*/

int main() {
	pwd();
	strcpy(home_dir, cur_dir);
	do {
		shell_prompt();
		read_parse();
		lsh_execute(array_tokens);
	} while (status);
	return 0;
}