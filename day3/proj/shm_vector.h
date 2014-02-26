#ifndef SHM_VECTOR_H
#define SHM_VECTOR_H

#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

class shm_vector
{
    key_t  shmkey_;
    int    shmid_;
    int   *shm_;

public:
    shm_vector(key_t shmkey, size_t size);
    ~shm_vector();

    void push_back(int element);
    size_t size();
    bool empty();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;
};

#endif // SHM_VECTOR_H
