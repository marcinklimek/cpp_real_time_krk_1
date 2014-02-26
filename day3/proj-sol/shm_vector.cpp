#include "shm_vector.h"
#include <errno.h>
#include <iostream>
#include <string.h>
#include <exception>

shm_vector::shm_vector(key_t shmkey, size_t size) : sema_(shmkey)
{
    shmkey_ = shmkey;
    size_   = size;
    shmid_  = shmget( shmkey_, (size_ + 1)*sizeof(int), 0666 );

    if ( shmid_ == -1 )
    {
        std::cout << "SHM -1 ! " << strerror(errno) << std::endl;
        if (errno == ENOENT)
        {
            shmid_  = shmget( shmkey_, (size_ + 1)*sizeof(int), 0666 |IPC_CREAT );
            map();
            clear();
        }
    }
    else
    {
        std::cout << "SHM exists " << std::endl;

        map();
    }
}

shm_vector::~shm_vector()
{
    shmdt( (char *) shm_ );
    if ( shmctl(shmid_, IPC_RMID, (struct shmid_ds *) 0) == -1 )
    {
        throw std::exception();
    }
}

void shm_vector::clear()
{
    sema_.lock();

    shm_[0] = 0;

    sema_.unlock();
}

void shm_vector::map()
{
    sema_.lock();

    shm_ = (int*)shmat(shmid_, 0, 0);
    if ( shm_ == (int*)-1 )
    {
        throw std::exception();
    }

    sema_.unlock();
}


void shm_vector::push_back(int element)
{
    sema_.lock();

    //std::cout << "push: " <<  element << std::endl;
    int top = shm_[0];

    //std::cout << " top: " <<  top << std::endl;
    //std::cout << " old val in shm: " <<  shm_[top] << std::endl;

    top++;
    shm_[0] = top;
    shm_[top]=element;

    //std::cout << " new top: " <<  shm_[0] << std::endl;
    //std::cout << " new val in shm: " <<  shm_[top] << std::endl;
    //std::cout.flush();

    sema_.unlock();
}

int shm_vector::pop()
{
    sema_.lock();

    int top = shm_[0];

    int value = -1;

    if ( top > 0 )
    {
        value = shm_[top];
        shm_[0]--;
    }

    sema_.unlock();

    return value;
}

size_t shm_vector::size()
{
    return shm_[0];
}

bool shm_vector::empty()
{
    return size() == 0;
}


int &shm_vector::operator[](size_t index)
{
    return shm_[index+1];
}

const int &shm_vector::operator[](size_t index) const
{
    return shm_[index+1];
}


////

template <class S_type>
shared_value<S_type>::shared_value(  )
{

    if ((shmid_ = shmget(IPC_PRIVATE, sizeof(S_type), IPC_CREAT | 0660)) < 0)
        exit(1);

    if ((shm_ptr_ = (S_type *) shmat(shmid_, NULL, 0)) == NULL)
        exit(2);
}

template <class S_type>
shared_value<S_type>::~shared_value(  )
{
    shmdt( (char *) shm_ptr_ );
    if ( shmctl(shmid_, IPC_RMID, (struct shmid_ds *) 0) == -1 )
    {
        //error
    }
}

template <class S_type>
void shared_value<S_type>::put( const S_type value )
{
    *shm_ptr_ = value;
}

template <class S_type>
S_type shared_value<S_type>::get( )
{
    static S_type value;
    value = *shm_ptr_;

    return value;
}

typedef shared_value<int>    shared_int;
typedef shared_value<char>   shared_char;
typedef shared_value<float>  shared_float;
typedef shared_value<double> shared_double;

