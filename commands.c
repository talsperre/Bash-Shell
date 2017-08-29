#include "header.h"

char const * sperm(__mode_t mode) {
    static char local_buff[16] = {0};
    int i = 0;
    // is directory ?
    if (S_ISDIR(mode)) local_buff[i] = 'd';
    else local_buff[i] = '-';
    i++;
    // user permissions
    if ((mode & S_IRUSR) == S_IRUSR) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWUSR) == S_IWUSR) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXUSR) == S_IXUSR) local_buff[i] = 'x';
    else local_buff[i] = '-';
    i++;
    // group permissions
    if ((mode & S_IRGRP) == S_IRGRP) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWGRP) == S_IWGRP) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXGRP) == S_IXGRP) local_buff[i] = 'x';
    else local_buff[i] = '-';
    i++;
    // other permissions
    if ((mode & S_IROTH) == S_IROTH) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWOTH) == S_IWOTH) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXOTH) == S_IXOTH) local_buff[i] = 'x';
    else local_buff[i] = '-';
    return local_buff;
}

int pinfo (char **args) 
{
	int pid;
	if(args[1]==NULL)
	{
		pid=curr_pid;
		
	}
	else
	{
		pid=atoi(args[1]);
	}

	printf("pid -- %d\n",pid);
		
	char* name2 = (char*)calloc(10024,sizeof(char));
	if(name2)
	{
	        sprintf(name2, "/proc/%d/status",pid);
	        FILE* f = fopen(name2,"r");
	        if(f)
	        {
	            size_t size;
	            size = fread(name2, sizeof(char), 1024, f);
	            if(size>0)
	            {
	                if('\n'==name2[size-1])
	                    name2[size-1]='\0';
	            }
	        }
	        fclose(f);
	}

	int pos=0;
	char *token;
	char **tokens = malloc(200 * sizeof(char*));
	char s[3]=" \t\n";

	token = strtok(name2, s);

	while (token != NULL) 
	{
			tokens[pos] = token;
			pos++;
			token = strtok(NULL, s);
	}
	int i;
	for(i=0;i<pos;i++)
	{
		//printf("%s\n",tokens[i]);
		if(strcmp(tokens[i],"VmSize:")==0)
		{
			printf("Memory -- %s {Virtual Memory}\n",tokens[i+1]);
		}
		if(strcmp(tokens[i],"Status:")==0)
		{

			printf("Status -- %s\n",tokens[i+1]);
		}
	}
	printf("Executable Path -- ");

	char path[PATH_MAX];
	char dest[PATH_MAX];
	memset(dest,0,sizeof(dest)); 
	// readlink does not null terminate!
	struct stat info;
		
	sprintf(path, "/proc/%d/exe", pid);
	if (readlink(path, dest, PATH_MAX) == -1)
	    perror("readlink");
	  else {
	    printf("%s\n", dest);
	  }

	return 1;
}

int ls (char **args) {
	int i, is_a = 0, is_l = 0, flag = 0;
	DIR *directory;
    char buf[MAXN];
    char dir_name[MAXN];
	for (i = 0; args[i] != NULL; i++) {
		if (strcmp(args[i], "ls") == 0) {
			continue;
		}
		else if (strcmp(args[i], "-a") == 0) {
			is_a = 1;
		}
		else if (strcmp(args[i], "-l") == 0) {
			is_l = 1;
		}
		else if (strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0) {
			is_l = 1;
			is_a = 1;
		}
		else {
			flag = 1;
			directory = opendir(args[i]);
			strcpy(dir_name, args[i]);
		}
	}
	if (!flag) {
		pwd();
		directory = opendir(cur_dir);
		strcpy(dir_name, cur_dir);
	}
	if (is_l) {
		while ((dir = readdir(directory)) != NULL) {

			sprintf(buf, "%s/%s", dir_name, dir->d_name);
			stat(buf, &st);

			if (!is_a && dir->d_name[0] == '.') {
				continue;
			}

			printf("%10.10s", sperm(st.st_mode));
			printf("%4d", st.st_nlink);

			if ((password = getpwuid(st.st_uid)) != NULL){
				printf(" %s", password->pw_name);
			}
			else {
				printf(" %d", st.st_uid);
			}
			if ((grp = getgrgid(st.st_gid)) != NULL) {
				printf(" %s", grp->gr_name);
			}
			else {
				printf(" %d", st.st_gid);
			}
			printf(" %9jd", (intmax_t)st.st_size);
			tm = localtime(&st.st_mtime);
			strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);
			printf(" %s %s\n", datestring, dir->d_name);
		}
	}
	else {
		while ((dir = readdir(directory)) != NULL) {

			sprintf(buf, "%s/%s", args[1], dir->d_name);
			stat(buf, &st);

			if (!is_a && dir->d_name[0] == '.') {
				continue;
			}
			printf("%s\n", dir->d_name);
		}
	}
	return 1;
}