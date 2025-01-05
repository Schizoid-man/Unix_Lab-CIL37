#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
int show_hidden = 0;
void list_directories(const char *dirpath)
{
        DIR *dir;
        struct dirent *entry;
        dir = opendir(dirpath);
        if(dir == NULL)
        {
                perror("opening");
                exit(EXIT_FAILURE);
        }
        while((entry = readdir(dir)) != NULL)
        {
                if(!show_hidden && (entry->d_name[0] == '.'))
                {
                        continue;
                }
                else{
                        printf("%s ", entry->d_name);
                }
        }
        closedir(dir);
}
int main(int argc, char *argv[])
{
        const char *dirpath = ".";
        for(int i = 1;i<argc;i++)
        {
                if(strcmp(argv[i],"-a") == 0)
                        show_hidden = 1;
                else
                        dirpath = argv[i];
        }
        list_directories(dirpath);
}
