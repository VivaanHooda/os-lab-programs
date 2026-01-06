#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

int main ()
{
    DIR *d;
    struct dirent *de;
    struct stat buf;
    int i,j;

    char P[10] = "rwxrwxrwx";
    char AP[10] = "----------";

    struct passwd *p;
    struct group *g;
    struct tm *t;
    char timeStr[26];

    d = opendir(".");
    if (d == NULL){
        perror("opendir");
        return 1;
    }
    readdir(d);
    readdir(d);
    while ((de = readdir(d)) != NULL){
        if (stat(de->d_name, &buf) == -1)
            continue;
        if (S_ISDIR(buf.st_mode)) printf ("d");
        else if (S_ISREG(buf.st_mode)) printf ("-");
        else if (S_ISCHR(buf.st_mode)) printf ("c");
        else if (S_ISBLK(buf.st_mode)) printf ("b");
        else if (S_ISLNK(buf.st_mode)) printf ("l");
        else if (S_ISFIFO(buf.st_mode)) printf ("p");
        else if (S_ISSOCK(buf.st_mode)) printf ("s");

        for (i =0, j = (1<<8); i < 9; i++, j>>=1)
            AP[i] = (buf.st_mode & j) ? P[i] : '-';
        printf ("%s ", AP);

        printf("%5ld ", buf.st_nlink);
        
        p = getpwuid(buf.st_uid);
        printf("%8s ", p->pw_name);

        g = getgrgid(buf.st_gid);
        printf("%-8.8s ",g->gr_name);

        printf("%8lld ", buf.st_size);

        t = localtime(&buf.st_mtime);
        strftime(timeStr, sizeof(timeStr), "%b %d %H:%M", t);
        printf(timeStr);
        printf(" ");

        printf ("%s\n", de->d_name);
    }
    closedir(d);
    return 0;
}