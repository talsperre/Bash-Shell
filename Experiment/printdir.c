#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>


struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];

char const * sperm(__mode_t mode) {
    static char local_buff[16] = {0};
    int i = 0;
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


int main (int argc, char const *argv[]) {
    DIR *dir;
    dir = opendir(argv[1]);
    printf("Hello %s\n", argv[1]);
    char buf[512];
    while ((dp = readdir(dir)) != NULL) {
        
        sprintf(buf, "%s/%s", argv[1], dp->d_name);
        stat(buf, &statbuf);

        printf("%10.10s", sperm(statbuf.st_mode));
        printf("%4d", statbuf.st_nlink);

        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
            //printf(" %-8.8s", pwd->pw_name);
            printf(" %s", pwd->pw_name);
        else
            //printf(" %-8d", statbuf.st_uid);
            printf(" %d", statbuf.st_uid);

        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
            //printf(" %-8.8s", grp->gr_name);
            printf(" %s", grp->gr_name);
        else
            //printf(" %-8d", statbuf.st_gid);
            printf(" %d", statbuf.st_gid);

        printf(" %9jd", (intmax_t)statbuf.st_size);
        tm = localtime(&statbuf.st_mtime);
        //strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);
        printf(" %s %s\n", datestring, dp->d_name);
    }
    return 0;
}