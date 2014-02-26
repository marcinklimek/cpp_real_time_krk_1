#ifndef SHM_VECTOR_H
#define SHM_VECTOR_H

#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include "shm_semaphore.h"


class shm_vector
{
    key_t  shmkey_;
    int    shmid_;
    int   *shm_;
    u_int  size_;
    shm_semaphore sema_;

    // copy constructor deleted
    //shm_vector(const shm_vector& v);
    // copying assignment deleted
    //shm_vector& operator=(const shm_vector& v) {}
    void map();
    void clear();

public:
    shm_vector(key_t shmkey, size_t size);
    ~shm_vector();
    void push_back(int element);
    int pop();
    size_t size();
    bool empty();
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
};


template <class S_type>
class shared_value
{
    int    shmid_;
    S_type *shm_ptr_;

    // copy constructor deleted
    shared_value(const shm_vector& v) {}
    // copying assignment deleted
    shared_value& operator=(const shared_value& v) {}

public:
    shared_value ( );
    ~shared_value( );
    void   put( const S_type );
    S_type get(  );

};


#endif // SHM_VECTOR_H
