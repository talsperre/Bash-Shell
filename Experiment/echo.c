#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int shell_echo(char * args[]) 
{
	if (args[1]==NULL)
	{
		printf("\n");
		return 1;
	}
	else
	{
		int i=1;
		while(args[i]!="")
		{
			write(1, args[i], strlen(args[i]));
			write(1," ",1);
			i++;
		}
		write(1,"\n",1);

	}

}
int main()
{
	char * arr[]={"echo","a","b","c","d",""};
	shell_echo(arr);
	char * arr1[]={"echo"};
	shell_echo(arr1);

}