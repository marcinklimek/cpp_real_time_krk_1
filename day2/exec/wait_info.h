#ifndef __WAIT_INFO__
#define __WAIT_INFO__

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void wait_info(pid_t w, int status)
{
    if (w == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("unfiltered status=%d\n", status);
    if (WIFEXITED(status))
    {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("killed by signal %d\n", WTERMSIG(status));
    }
    else if (WIFSTOPPED(status))
    {
        printf("stopped by signal %d\n", WSTOPSIG(status));
    }
    else if (WIFCONTINUED(status))
    {
        printf("continued\n");
    }
}

#endif /* __WAIT_INFO__ */
