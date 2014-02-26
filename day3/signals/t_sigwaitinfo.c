#include <signal.h>
#include <time.h>
#include "../inc/misc_functions.h"

int main(int argc, char *argv[])
{
    int sig;
    siginfo_t si;
    sigset_t allSigs;

    printf("PID is %ld\n", (long) getpid());

    /* Block all signals (except SIGKILL and SIGSTOP) */

    sigfillset(&allSigs);
    if (sigprocmask(SIG_SETMASK, &allSigs, NULL) == -1)
        errExit("sigprocmask");

    printf("signals blocked\n");

    /* Delay so that signals can be sent to us */
    printf("delay 5 seconds\n");
    sleep( 5 );
    printf("finished delay\n");

    for (;;) 
    { 
        /* Fetch signals until SIGINT (^C) or SIGTERM */
        
        sig = sigwaitinfo(&allSigs, &si);
        if (sig == -1)
            errExit("sigwaitinfo");

        if (sig == SIGINT || sig == SIGTERM)
            exit(EXIT_SUCCESS);

        printf("got signal: %d (%s)\n", sig, strsignal(sig));
        
        printf("    si_signo=%d, si_code=%d (%s), si_value=%d\n",
                si.si_signo, si.si_code,
                (si.si_code == SI_USER) ? "SI_USER" :
                (si.si_code == SI_QUEUE) ? "SI_QUEUE" : "other",
                si.si_value.sival_int);
        
        printf("    si_pid=%ld, si_uid=%ld\n",
                (long) si.si_pid, (long) si.si_uid);
    }
}
