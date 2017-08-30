#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "header.h"

int INTERVAL;   


void dirty(void);

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int nightswatch(int n)
{

	INTERVAL=n*1000;

  	struct itimerval it_val;  /* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms, 
   * but the setitimer call needs seconds and useconds. */
	  if (signal(SIGALRM, (void (*)(int)) dirty) == SIG_ERR) {
	    perror("Unable to catch SIGALRM");
	    exit(1);
	  }
	  it_val.it_value.tv_sec =     INTERVAL/1000;
	  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;   
	  it_val.it_interval = it_val.it_value;
	  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
	    perror("error calling setitimer()");
	    return 0;
		}
	    while (getch()!='q')
	    {
	      pause();
		}  
		signal(SIGINT, SIG_DFL);
		it_val.it_value.tv_sec =     0;
		it_val.it_value.tv_usec =    0;   
		it_val.it_interval = it_val.it_value;
		 setitimer(ITIMER_REAL, &it_val, NULL);
		 return 1;
    
}

    /*
     * DoStuff
     */
void dirty(void)
{

	char* name2 = (char*)calloc(10024,sizeof(char));
	if(name2)
	{
	        sprintf(name2, "/proc/meminfo");
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
	char **tokens = malloc(2000 * sizeof(char*));
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
		if(strcmp(tokens[i],"Dirty:")==0)
		{
			printf("%s KB\n",tokens[i+1]);
			break;
		}
		
	}

}

