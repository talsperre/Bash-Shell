#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#define MAXN 1234
char *pwd();
char *get_user_name();
char *print_dir(char cur_dir[]);
int cd(char *args[]);
int read_parse();

char cd_dir[MAXN];
char hostname[HOST_NAME_MAX];
char username[LOGIN_NAME_MAX];
char home_dir[MAXN];
char cur_dir[MAXN];
char res[MAXN];
char inp_string[1024];
char ** array_tokens;

int array_token_size;