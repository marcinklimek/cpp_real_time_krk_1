#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "../inc/misc_functions.h"

void catch_int(int signum)
{
    printf("Handler %d\n", signum);
}

int main(int argc, char const *argv[])
{
    //static struct sigaction action;
    //static struct sigaction old_action;
    int i;
    
    //action.sa_handler = catch_int;
    //sigaction( SIGINT, &action, NULL );

    printf("PID: %d\n", getpid());

    signal( SIGINT, catch_int);

    for( i=0; i<300; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }    

    return 0;
}
