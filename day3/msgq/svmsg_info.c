#include "../inc/misc_functions.h"
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    struct msginfo info;
    int s;

    s = msgctl(0, MSG_INFO, (struct msqid_ds *) &info);
    if (s == -1)
        errExit("msgctl");

    printf("Maximum ID index = %d\n", s);
    printf("queues in_use    = %ld\n", (long) info.msgpool);
    printf("msg_bytes        = %ld\n", (long) info.msgmax);
    exit(EXIT_SUCCESS);
}
