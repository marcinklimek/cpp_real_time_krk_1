#include <iostream>
#include <sys/ipc.h>

#include <sys/sem.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

typedef union _semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;

int main(int argc, char **argv)
{

    key_t semkey = 0x0b;
    int   semid;

    semid = semget( semkey, 1, 0666 | IPC_CREAT);

    if (semid == -1)
    {
        std::cout << strerror( errno ) << std::endl;

        exit(1);
    }

    semun arg;
    arg.val = 1;

    semctl( semid, 0, SETVAL, arg);
    std::cout << semctl( semid, 0, GETVAL, 0) << std::endl;

    struct sembuf sem_info;

    sem_info.sem_num =  0;
    sem_info.sem_op  = -1;
    sem_info.sem_flg = SEM_UNDO;
    printf("LOCK 1\n");
    semop( semid, &sem_info, 1);

    printf("LOCK 2\n");
    semop( semid, &sem_info, 1);
    printf("LOCK 3\n");

    std::cout << semctl( semid, 0, GETVAL, 0) << std::endl;

    sem_info.sem_num =  0;
    sem_info.sem_op  =  1;
    sem_info.sem_flg = SEM_UNDO;
    semop( semid, &sem_info, 1);

    std::cout << semctl( semid, 0, GETVAL, 0) << std::endl;

    return 0;
}
