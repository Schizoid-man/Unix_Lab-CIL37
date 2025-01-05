#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

void list_permissions(struct stat fileStat)
{
        printf((S_ISDIR(fileStat.st_mode))?"d":"-");
        printf((fileStat.st_mode & S_IRUSR)?"r":"-");
        printf((fileStat.st_mode & S_IWUSR)?"w":"-");
        printf((fileStat.st_mode & S_IXUSR)?"x":"-");
        printf((fileStat.st_mode & S_IRGRP)?"r":"-");
        printf((fileStat.st_mode & S_IWGRP)?"w":"-");
        printf((fileStat.st_mode & S_IXGRP)?"x":"-");
        printf((fileStat.st_mode & S_IROTH)?"r":"-");
        printf((fileStat.st_mode & S_IROTH)?"w":"-");
        printf((fileStat.st_mode & S_IXOTH)?"x":"-");
}
void list_directories(const char *dirpath) {
        DIR *dir;
        struct dirent *entry;
        struct stat fileStat;
        char fullpath[1024];
        dir = opendir(dirpath);
        if(dir == NULL){
                perror("opening");
                exit(EXIT_FAILURE);
        }
        while((entry = readdir(dir)) != NULL)
        {
                snprintf(fullpath, sizeof(fullpath),"%s/%s",dirpath, entry->d_name);

                if(stat(fullpath, &fileStat) == -1)
                {
                        perror("stat");
                        continue;
                }
                printf("%ld", (long)fileStat.st_ino);
                list_permissions(fileStat);
                printf("%ld", (long)fileStat.st_nlink);
                printf("%s %s", getpwuid(fileStat.st_uid)->pw_name, getgrgid(fileStat.st_gid)->gr_name);
                printf("%5ld", (long)fileStat.st_size);
                char timebuf[80];
                struct tm *timeinfo = localtime(&fileStat.st_mtime);
                strftime(timebuf, sizeof(timebuf), "%b %d %H %M", timeinfo);
                printf("%s ", timebuf);
                printf("%s \n", entry->d_name);
        }
        closedir(dir);
}
void main(int argc, char *argv[])
{
        const char *dirpath;
        if(argc > 1)
        {
                dirpath=argv[1];
        }
        else
                dirpath = ".";

        list_directories(dirpath);
}
