#include <sys/types.h>
#include <sys/sem.h>
#include "../inc/misc_functions.h"

typedef union _semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;

int
main(int argc, char *argv[])
{
    semun dummy;

    int id = 10;

    if (semctl(id, 0, IPC_RMID, dummy) == -1)
        errExit("semctl");

    exit(EXIT_SUCCESS);
}
