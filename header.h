#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#define MAXN 1234
#define DELIM " \t\r\n\a"

char *pwd();
char *get_user_name();
char *print_dir(char cur_dir[]);
char **read_parse();
int cd(char *args[]);
int shell_prompt ();
int echo(char *args[]);
int shell_exit();
int ls(char *args[]);
int pinfo(char *args[]);
int launch (char **args); 
int execute(char **args);
int loop();

typedef struct process {
	pid_t pid;
	char name[MAXN];
} proc;
proc array_process[MAXN];

struct dirent *dir;
struct stat st;
struct passwd *password;
struct group *grp;
struct tm *tm;
char datestring[MAXN];

char hostname[HOST_NAME_MAX];
char username[LOGIN_NAME_MAX];
char home_dir[MAXN];
char cur_dir[MAXN];
char res[MAXN];

int array_token_size;
int proc_idx;
int curr_pid;