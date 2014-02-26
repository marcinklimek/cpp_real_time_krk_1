#include "../inc/misc_functions.h"
#include <signal.h>

int main(int argc, char *argv[])
{
    int sig, numSigs, j, sigData;
    union sigval sv;

    if ( argc < 2 )
        exit(1);

    pid_t pid = atoi( argv[1]);
    sig = SIGRTMIN;
    sigData = 0xcafebabe;
    numSigs = 10;

    printf("%s: PID is %ld, UID is %ld\n", argv[0],
            (long) getpid(), (long) getuid());


    for (j = 0; j < numSigs; j++) 
    {
        sv.sival_int = sigData + j;
        if (sigqueue(pid, sig, sv) == -1)
            errExit("sigqueue %d", j);
    }

    exit(EXIT_SUCCESS);
}
