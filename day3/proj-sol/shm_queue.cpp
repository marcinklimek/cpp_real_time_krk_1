#include "shm_queue.h"
#include <errno.h>
#include <iostream>
#include "shm_queue.h"
#include <cstdio>
#include <exception>

shm_queue::shm_queue( const key_t key )
{
    ipckey_ = key;
    msqid_  = -1;

    if ( exist(ipckey_) )
    {
        acquire();
    }
    else
    {
        create();
    }
}

shm_queue::~shm_queue()
{
    remove();
}


void shm_queue::remove(  )
{
    if ( msgctl( msqid_, IPC_RMID, (struct msqid_ds *) 0 ) == -1 )
    {
        throw std::exception();//error
    }

}

void shm_queue::enque( void *msg, int msg_size )
{
    if ( msgsnd( msqid_, msg, msg_size, 0 ) == -1 )
    {
        throw std::exception();
    }
}

int shm_queue::deque( void *msg, int msg_size, int msg_type )
{
    int n;
    memset( msg, 0x0, msg_size );        // clear space

    if ( (n=msgrcv( msqid_, msg, msg_size, msg_type, 0)) == -1 )
    {
        throw std::exception();
    }

    return n;
}

bool shm_queue::exist( const key_t key )
{
    return (msgget(ipckey_, 0) != -1);
}

void shm_queue::create( )
{
    if ( (msqid_=msgget(ipckey_, IPC_CREAT|0660)) == -1 )
    {
        throw std::exception();
    }
}

void shm_queue::acquire( )
{
    if ( (msqid_=msgget(ipckey_, 0)) == -1 )
    {
        throw std::exception();// error
    }
}
