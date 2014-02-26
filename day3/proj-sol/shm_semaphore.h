#ifndef SHM_SEMAPHORE_H
#define SHM_SEMAPHORE_H
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

class shm_semaphore
{
    key_t semkey_;
    int semid_;
    u_int numsem_;

public:

    shm_semaphore(key_t semkey);

    int get_value();

    void lock();
    void unlock();

    ~shm_semaphore();
};

#endif // SHM_SEMAPHORE_H
