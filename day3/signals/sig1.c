#include <signal.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    static struct sigaction action;
    static struct sigaction old_action;
    int i;
    

    for( i=0; i<30; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }    

    return 0;
}