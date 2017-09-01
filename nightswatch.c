#include "header.h"
/* Function:
	Gets the characteer from the stdin buffer
	Input: void
	Output: return asccii value
*/
void dirty(void) ;

int getch(void) {
	struct termios oldattr, newattr;
	int ch;
	if (tcgetattr(STDIN_FILENO, &oldattr) != 0) {
		perror("tcgetattr() error");
	}
	else {
		newattr = oldattr;
		newattr.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &newattr) != 0) {
			perror("tcsetattr() error");
		}
		ch = getchar();
		if (tcsetattr(STDIN_FILENO, TCSANOW, &oldattr) != 0) {
			perror("tcsetattr() error");
		}
		return ch;
	}
}
/* Function:
	Repetas the command after n seconds
	Input: n - after how many seconds to run the command
	Output: calls the funtion after n second and check for key q also
*/
int nightswatch(int n) {

	INTERVAL = n * 1000;

    struct itimerval it_val; /* for setting itimer */

    /* Upon SIGALRM, call DoStuff().
     * Set interval timer.  We want frequency in ms, 
     * but the setitimer call needs seconds and useconds. */
	if (signal(SIGALRM, (void( * )(int)) dirty) == SIG_ERR) {
		perror("Unable to catch SIGALRM");
		exit(1);
	}

	it_val.it_value.tv_sec = INTERVAL / 1000;
	it_val.it_value.tv_usec = (INTERVAL * 1000) % 1000000;
	it_val.it_interval = it_val.it_value;
	
	if (setitimer(ITIMER_REAL, & it_val, NULL) == -1) {
		perror("error calling setitimer()");
		return 0;
	}
	
	while (getch() != 'q') {
		pause();
	}
	
	signal(SIGINT, SIG_DFL);
	it_val.it_value.tv_sec = 0;
	it_val.it_value.tv_usec = 0;
	it_val.it_interval = it_val.it_value;
	setitimer(ITIMER_REAL, & it_val, NULL);
	return 1;

}

/*
 * Finds the dirty memory
 */

void dirty(void) {

	char * name2 = (char * ) calloc(10024, sizeof(char));
	if (!name2) {
		fprintf(stderr, "Allocation error\n");
    	exit(EXIT_FAILURE);
    }
	
	if (name2) {
		sprintf(name2, "/proc/meminfo");
		FILE * f = fopen(name2, "r");
		if (f) {
			size_t size;
			size = fread(name2, sizeof(char), 1024, f);
			if (size > 0) {
				if ('\n' == name2[size - 1])
					name2[size - 1] = '\0';
			}
		}
		else {
			fprintf(stderr, "Failed to open file \"%s\"\n", name2);
			exit(1);
		}
		fclose(f);
	}

	int pos = 0;
	char * token;
	char ** tokens = malloc(2000 * sizeof(char * ));
	char s[3] = " \t\n";

	if (!tokens) {
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(name2, s);

	while (token != NULL) {
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, s);
	}
	int i;

	for (i = 0; i < pos; i++) {
		if (strcmp(tokens[i], "Dirty:") == 0) {
			printf("%s KB\n", tokens[i + 1]);
			break;
		}
	}
}