#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void catch_int(int signum)
{
    printf("Handler %d\n", signum);
}


int main(int argc, char const *argv[])
{
    static struct sigaction action;
    char buf[512];
    int nread;
    //action.sa_flags = SA_RESTART;
    action.sa_handler = catch_int;
    sigaction( SIGUSR1, &action, NULL);
    //signal( SIGUSR1, catch_int);

    printf("PID: %d\n", getpid());

    nread = read (fileno(stdin), buf, sizeof(buf));
    if (nread < 0) 
    {
        printf( "nred < 0, %s\n", strerror( errno ) );
        return 1;
    }

    printf("Num read = %d -> %s\n", nread, buf);

    return 0;
}

