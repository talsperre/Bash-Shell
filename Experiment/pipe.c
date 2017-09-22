#include "header.h"

int pipeHandler(char **args)
{   
	pid_t pid;
	

	char ** comm=(char**)malloc(sizeof(char*)*1024);
	int odd[2];
	int even[2];
	int i,j,k,flag=0;
	int pipes=0;
	
	for(i=0;args[i]!=NULL;i++)
	{
		if(strcmp(args[i],"|")==0)
		{
			pipes++;		
		}
	}
	pipes++;
	//printf("No is pipes are %d\n",pipes);
	int curr_pipe=0;
	
	for(i=0;args[i]!=NULL && flag!=1;)
	{
		//printf("%d %d",i,j);
		k=0;

		for(j=i;args[j]!="|";j++)
		{
			comm[k++]=args[j];
			if(args[j]==NULL)
			{
				flag=1;
				break;
			}
		}
		comm[k++]=NULL;
		i=j+1;

		/*for(m=0;m<k-1;m++)
		{
			printf("%s\n",comm[m]);
		}*/
		
		

		if(curr_pipe%2==1){pipe(odd);}
		
		else if(curr_pipe%2==0){pipe(even);}

		pid=fork();

		if(pid==-1)
		{
			perror("Child process could not be created\n");
            return 1;
		}
		//child process
		else if(pid==0)
		{
			if(curr_pipe==0)
			{
				dup2(even[1],STDOUT_FILENO);
			}
			else if (curr_pipe == pipes - 1)
			{
                if (pipes % 2 == 1)
                { //currently on index pipe-1 if pipe is odd then current index is even do open odd for input and will used for this process 
                    dup2(odd[0],STDIN_FILENO);
                }else
                { // for even number of commands
                    dup2(even[0],STDIN_FILENO);
                }
            }
            else
            {
            	if(curr_pipe % 2 ==1)
            	{
            		dup2(even[0],STDIN_FILENO);
            		dup2(odd[1],STDOUT_FILENO);

            	}
            	else
            	{
            		dup2(odd[0],STDIN_FILENO);
            		dup2(even[1],STDOUT_FILENO);

            	}
            }
            if(execvp(comm[0],comm)==-1)
            {
            	return 1;
            }	

		}
		//parentprocess
		
		if (curr_pipe == 0)
		{
        	close(even[1]);
    	}
   		else if (curr_pipe == pipes - 1)
   		{
        	if (pipes % 2 != 0)
        	{                 
            	close(odd[0]);
        	}
        	else
        	{                  
            	close(even[0]);
        	}
        }
    	else
    	{
        	if (curr_pipe % 2 != 0)
        	{                    
            	close(even[0]);
            	close(odd[1]);
            }
        	else
        	{                  
            	close(odd[0]);
            	close(even[1]);
        	}
        }
        curr_pipe++;
        waitpid(pid,NULL,0);
	
		//printf("%d %d",i,j);
		
	}
	return 1;
}