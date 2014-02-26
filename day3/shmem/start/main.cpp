#include <iostream>
#include <sys/ipc.h>

#include <sys/shm.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MEM_SIZE 100

int main(int argc, char **argv)
{

    key_t shm_key = 0x0b;

    int* shm;

    int shm_id = shmget( shm_key, MEM_SIZE*sizeof(int), 0666 | IPC_CREAT );

    if( shm_id == -1)
    {
        std::cout <<  strerror( errno ) << std::endl;

        exit(1);
    }

    shm = (int*)shmat(shm_id, 0, 0);
    shm[10] = 123;

    std ::cout << shm[10] << std::endl;

    return 0;
}
