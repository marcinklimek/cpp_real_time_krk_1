#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> /* vsnprintf() */
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void handler(int signal)
{
    counter++;
    printf("Signal handler called = %d\n", counter);
    fflush(stdout);
}

int main(int argc, char const *argv[])
{
    int i;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction( SIGRTMIN, &sa, NULL);

    for(i = 0; i<5; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf("Signal handler called = %d", counter);

    return 0;
}
