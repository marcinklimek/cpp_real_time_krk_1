#define _GNU_SOURCE

#include <sys/wait.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int childFunc(void *arg)
{
    if (close(*((int *) arg)) == -1)
        exit(-1);

    return 0;
}

int main(int argc, char *argv[])
{
    const int STACK_SIZE = 65536;       /* rozmiar stosu dla sklonowanej funkcji */
    char *stack;                        /* początek bufora*/
    char *stackTop;                     /* konieci */
    int s, fd, flags;

    fd = open("/dev/null", O_RDWR);
    if (fd == -1)
        exit(-1);

    /* co klonować */
    flags = (argc > 1) ? CLONE_FILES : 0;

    /* stack */
    stack = (char*)malloc(STACK_SIZE);
    if (stack == NULL)
        exit(-1);

    stackTop = stack + STACK_SIZE;      /* szczyt stosu */

    if (clone(childFunc, stackTop, flags, (void *) &fd) == -1)
        exit(-1);

    if (waitpid(-1, NULL, __WCLONE) == -1)
        exit(-1);

    printf("dziecko zakonczylo \n");

    /* Did close() of file descriptor in child affect parent? */

    s = write(fd, "1", 1);
    if (s == -1 && errno == EBADF)
        printf("FD %d zamknięty\n", fd);
    else if (s == -1)
        printf("write() na FD=%d nie powiodl sie (%s)\n",
               fd, strerror(errno));
    else
        printf("write() na FD=%d powiodl sie\n", fd);

    exit(EXIT_SUCCESS);
}
