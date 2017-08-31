#include "header.h"
int main()
{
	

	char * arr[]={"cd","/home",NULL};
	cd(arr);
	printf("%s\n",pwd());

	char * arr1[]={"cd","..",NULL};
	cd(arr1);
	printf("%s\n",pwd());

	char * arr2[]={"echo","kanay",NULL};
	
	echo(arr2);

	/*char * arr[]={"cd","/home",NULL};
	cd(arr);
	printf("%s\n",pwd());
	*/
}