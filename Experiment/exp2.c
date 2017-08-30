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
#include <sys/time.h>       /* for setitimer */
#include <unistd.h>     /* for pause */
#include <signal.h>     /* for signal */
/*
 * setitimer.c - simple use of the interval timer
 */

#include <sys/time.h>       /* for setitimer */
#include <unistd.h>     /* for pause */
#include <signal.h>     /* for signal */

#define INTERVAL 10000       /* number of milliseconds to go off */

/* function prototype */
void DoStuff(void);
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
int main(int argc, char *argv[])
{

  struct itimerval it_val;  /* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms, 
   * but the setitimer call needs seconds and useconds. */
  if (signal(SIGALRM, (void (*)(int)) DoStuff) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
  it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;   
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("error calling setitimer()");
    exit(1);
	}
    while (getch()!='q')
    {
      pause();
	}       
}

    /*
     * DoStuff
     */
void DoStuff(void)
{

      printf("Timer went off.\n");

}

