#ifndef SHM_QUEUE_H
#define SHM_QUEUE_H

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>

class shm_queue
{
    int      msqid_;
    key_t    ipckey_;

public:
    shm_queue (key_t shqkey);
    ~shm_queue();

    void remove( );
    void enque( void *, int );
    int  deque( void *, int size, int type);
    bool exist( const key_t shqkey);
    void create(  );
    void acquire(  );

};

#define MAX_MESSAGE 1024

typedef struct
{
    long int type;
    int data;
} message_int;



#endif // SHM_QUEUE_H
