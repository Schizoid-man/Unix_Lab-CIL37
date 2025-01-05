#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
        int fd, new_fd;
        char filename[] = "copy.txt";
        fd = open(filename,O_RDWR);
        ssize_t bytesRead;
        char buffer [1024];
        if(fd == -1)
        {
                perror("Error opening file");
                exit(EXIT_FAILURE);
        }
        lseek(fd,0,SEEK_END);
        new_fd = dup(fd);
        if(new_fd == -1)
        {
                perror("Error duplicating file");
                exit(EXIT_FAILURE);
        }
        int n;
        printf("Enter the number of characters to copy");
        scanf("%d", &n);
        lseek(fd, -n, SEEK_END);
        bytesRead = read(fd, buffer, n);
        if(bytesRead <= 0)
        {
                perror("Error reading file");
                exit(EXIT_FAILURE);
                close(fd);
                close(new_fd);
        }
        if((write(new_fd, buffer, bytesRead))!=bytesRead)
        {
                perror("Error writing to file");
                close(fd);
                close(new_fd);
                exit(EXIT_FAILURE);
        }
        printf("File appended successfully! \n");
        close(fd);
        close(new_fd);
        return 0;
}
