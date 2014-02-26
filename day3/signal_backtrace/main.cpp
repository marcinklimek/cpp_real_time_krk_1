#define __USE_GNU

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <execinfo.h>

/* get REG_EIP from ucontext.h */

#include <ucontext.h>
#ifdef __x86_64__
#define REG_EIP REG_RIP
#endif

void bt_sighandler(int sig, siginfo_t *info, void *context)
{

    void *trace[16];
    char **messages = (char **)NULL;
    int i, trace_size = 0;
    ucontext_t *uc = (ucontext_t *)context;

    /* siginfo_t */
    if (sig == SIGSEGV)
    {
        printf("Got signal %d, faulty address is %p, "
               "from %p\n", sig, info->si_addr,
               (void*)uc->uc_mcontext.gregs[REG_EIP]);
    }
    else
        printf("Got signal %d#92;n", sig);

    trace_size = backtrace(trace, 16);

    /* overwrite sigaction with caller's address */
    trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

    messages = backtrace_symbols(trace, trace_size);

    /* skip first stack frame (points here) */
    printf("[bt] Execution path:\n");
    for (i=1; i<trace_size; ++i)
        printf("[bt] %s\n", messages[i]);

    exit(0);
}


int func_a(int a, char b)
{

    char *p = (char *)0xdeadbeef;

    a = a + b;
    *p = 10;  /* CRASH here!! */

    return 2*a;
}


int func_b()
{

    int res, a = 5;

    res = 5 + func_a(a, 't');

    return res;
}


int main()
{

    /* Install our signal handler */
    struct sigaction sa;

    sa.sa_sigaction = bt_sighandler;
    sigemptyset (&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    printf("%d\n", func_b());

}
