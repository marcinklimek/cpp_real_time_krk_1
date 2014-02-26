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

    void enque(int value, int type);
    int  deque(int type);
};

typedef struct
{
    long int type;
    int data;
} message_int;



#endif // SHM_QUEUE_H
