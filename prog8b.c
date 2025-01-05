#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void list_directories(const  char *dirpath)
{
        DIR *dir;
        struct dirent *entry;
        struct stat fileStat;
        dir = opendir(dirpath);
        if(dir == NULL)
        {
                perror("Error opening file");
                exit(EXIT_FAILURE);
        }
        while((entry = readdir(dir))!= NULL)
        {
                if(entry->d_name[0] == '.')
                        continue;
                printf("%s \n", entry->d_name);
        }
        closedir(dir);
}
int main()
{
        const char *dirpath;
        dirpath = ".";
        list_directories(dirpath);
}
