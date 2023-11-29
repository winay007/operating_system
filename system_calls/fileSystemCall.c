#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// void readFromFile(){

// }

int main()
{
    int fd1 = open("demo.txt", O_RDWR);
    int fd2 = open("demo.txt", O_RDWR);
    char *c = (char *)calloc(100, sizeof(char));

    if (fd1 < 0)
    {
        printf("error\n");
        return 0;
    }
    // printf("f = %d\n",&fd1);
    int size = 0;
    size = write(fd1, "hello guys chai!!\n", strlen("hello guys chai!!\n"));
    read(fd2, c, size);

    printf("filData = ");
    printf("%s\n", c);

    if (close(fd2) < 0)
    {
        printf("error\n");
        return 0;
    }
    printf("File closed successfully");

    return 0;
}