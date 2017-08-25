#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char const *argv[]) {
	shell_loop();
	return 0;
}