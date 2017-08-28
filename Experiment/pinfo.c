#include <stdio.h>
#include <stdlib.h>
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

int main()
{
	int pid;
	char ans[1024];
	//cin>>pid;
	pid=getpid();

	char* name1 = (char*)calloc(1024,sizeof(char));
	if(name1)
	{
	        sprintf(name1, "/proc/%d/cmdline",pid);
	        FILE* f = fopen(name1,"r");
	        if(f)
	        {
	            size_t size;
	            size = fread(name1, sizeof(char), 1024, f);
	            if(size>0)
	            {
	                if('\n'==name1[size-1])
	                    name1[size-1]='\0';
	            }
	        }
	            fclose(f);
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
	//printf("%s",name2);
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
			printf("Memory -- %s\n",tokens[i+1]);
		}
		if(strncmp(tokens[i],"St",2)==0)
		{

			printf("Status -- %s\n",tokens[i+1]);
		}
	}
	printf("Executable Path -- ");
	char path[PATH_MAX];
	char dest[PATH_MAX];
	memset(dest,0,sizeof(dest)); // readlink does not null terminate!
	struct stat info;
		
	sprintf(path, "/proc/%d/exe", pid);
	if (readlink(path, dest, PATH_MAX) == -1)
	    perror("readlink");
	  else {
	    printf("%s\n", dest);
	  }
	//printf("status -- %s\n",tokens[2]);
	//printf("virtual memory -- %s\n",tokens[15]);
	
}
