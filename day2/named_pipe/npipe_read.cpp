#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 64

int main(int argc, char const *argv[])
{
    int fd;

    char buf[BUF_SIZE];

    /*if( mkfifo("my-pipe", 0666 ) == -1)
    {
        printf("error");
        exit(1);
    }*/


    fd = open( "my-pipe", O_RDWR );

    while( 1 )
    {
        memset( buf, 0, sizeof(buf) );

        int num_read = read(fd, buf, BUF_SIZE-1 );

        printf("num read: %d  -> %s\n", num_read, buf);
    }

    return 0;
}