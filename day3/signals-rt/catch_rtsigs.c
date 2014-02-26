#include "../inc/misc_functions.h"
#include <signal.h>

static volatile int handlerSleepTime;
static volatile int sigCnt = 0;         /* Number of signals received */
static volatile int allDone = 0;

static void             /* Handler for signals established using SA_SIGINFO */
siginfoHandler(int sig, siginfo_t *si, void *ucontext)
{
    /* UNSAFE: This handler uses non-async-signal-safe functions */
    /* SIGINT or SIGTERM can be used to terminate program */

    if (sig == SIGINT || sig == SIGTERM) {
        allDone = 1;
        return;
    }

    sigCnt++;
    printf("caught signal %d\n", sig);

    printf("    si_signo=%d, si_code=%d (%s), ", si->si_signo, si->si_code,
            (si->si_code == SI_USER) ? "SI_USER" :
            (si->si_code == SI_QUEUE) ? "SI_QUEUE" : "other");
    printf("si_value=0x%x\n", si->si_value.sival_int);
    printf("    si_pid=%ld, si_uid=%ld\n",
            (long) si->si_pid, (long) si->si_uid);

    if ( handlerSleepTime > 0 ) 
        sleep(handlerSleepTime);
}

int
main(int argc, char *argv[])
{
    struct sigaction sa;
    int sig;

    printf("PID is %ld\n", (long) getpid());

    handlerSleepTime = 1;

    sa.sa_sigaction = siginfoHandler;
    sa.sa_flags = SA_SIGINFO;
    sigfillset(&sa.sa_mask);

    for (sig = 1; sig < NSIG; sig++)
        if (sig != SIGTSTP && sig != SIGQUIT)
            sigaction(sig, &sa, NULL);

    while (!allDone)                    /* Wait for incoming signals */
        pause();

    printf("Caught %d signals\n", sigCnt);
    exit(EXIT_SUCCESS);
}
