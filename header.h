#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#define MAXN 1234
#define DELIM " \t\r\n\a"

char *pwd();
char *get_user_name();
char *print_dir(char cur_dir[]);
char **read_parse();
char ** array_tokens;
int cd(char *args[]);
int shell_prompt ();
int echo(char *args[]);
int shell_exit();

//char cd_dir[MAXN];
char hostname[HOST_NAME_MAX];
char username[LOGIN_NAME_MAX];
char home_dir[MAXN];
char cur_dir[MAXN];
char res[MAXN];

int array_token_size;