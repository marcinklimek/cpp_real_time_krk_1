#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MSG_SIZE 100

typedef struct
{

    long type;
    char data[MSG_SIZE];
} message_t;

enum
{
    MY_TYPE = 1
};

int main(int argc, char **argv)
{
    key_t queue_key = 0x0b;
    int queue_id;

    queue_id = msgget( queue_key, IPC_CREAT | 0666 );

    if ( queue_id == -1 )
    {
        std::cout << "msgget failed " << strerror( errno ) << std::endl;
        exit(1);
    }

    // wyslanie
    {
        message_t msg;
        memset(&msg, 0, sizeof(message_t));
        msg.type = MY_TYPE;
        strcpy( msg.data, "ABCD" );

        int result = msgsnd( queue_id, &msg, sizeof(message_t), 0 );

        std::cout << "Result: " << result << std::endl;
    }

    //odbior
    {
        message_t msg;
        memset(&msg, 0, sizeof(message_t));

        msgrcv( queue_id, &msg, sizeof(message_t), 1, 0);
        std::cout << "RCV: "<< msg.data << std::endl;
    }

    msqid_ds stats;
    msgctl( queue_id, IPC_STAT, &stats);

    std::cout << stats.msg_qnum << std::endl;



    return 0;
}
