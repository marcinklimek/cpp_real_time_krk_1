#include "shm_semaphore.h"
#include "limits.h"
#include "iostream"
#include "exception"

typedef union _semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;


shm_semaphore::shm_semaphore(key_t semkey)
{
    int status = 0;

    semkey_ = semkey;

    if((semid_ = semget(semkey_, 1, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
    {
        if(errno == EEXIST)
        {
            semid_ = semget(semkey_, 1, 0);
        }
        else
        {
            /* jeśli utworzony */
            semun arg;
            arg.val = 1;
            status = semctl(semid_, 1, SETVAL, arg);
        }

        if(semid_ == -1 || status == -1)
        {
            //error
	    throw std::exception();
        }
    }
    semun semopts;

    semopts.val = 0;
    semctl( semid_, 0, SETVAL, semopts);
}

int shm_semaphore::get_value()
{
    int value = semctl(semid_, 0, GETVAL, 0);

    return value;
}

void shm_semaphore::lock()
{
    struct sembuf p_buf;

    p_buf.sem_num = 0;
    p_buf.sem_op  = 1;
    p_buf.sem_flg = SEM_UNDO;

    if(semop(semid_, &p_buf, 1) == -1)
    {
        throw std::exception();
    }
}

void shm_semaphore::unlock()
{
    struct sembuf p_buf;

    p_buf.sem_num = 0;
    p_buf.sem_op  = -1;
    p_buf.sem_flg = SEM_UNDO;

    if(semop(semid_, &p_buf, 1) == -1)
    {
        throw std::exception();
    }
}

shm_semaphore::~shm_semaphore()
{

}
