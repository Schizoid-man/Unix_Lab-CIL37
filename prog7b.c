#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
void removeEmptyFiles(char *path)
{
        DIR *dir;
        struct dirent *entry;
        struct stat fileStat;
        char fullpath[1024];

        if((dir=opendir(path)) == NULL)
        {
                perror("Error openig dir");
                exit(EXIT_FAILURE);
        }
        while((entry = readdir(dir)) != NULL)
        {
                snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if(stat(fullpath, &fileStat) < 0)
        {
                perror("stat");
                exit(EXIT_FAILURE);
        }
        if(S_ISREG(fileStat.st_mode) && fileStat.st_size == 0)
        {
                if(unlink(fullpath) == 0)
                {
                        printf("File removed successfully");

                }
                else
                        perror("error removing file");
        }
        }
        closedir(dir);
}
int main(int argc, char *argv[])
{
        if(argc != 2)
        {
                fprintf(stderr,"Usage: %s <directory>", argv[1]);
                exit(EXIT_FAILURE);
        }
        removeEmptyFiles(argv[1]);
}
