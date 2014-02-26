#include <iostream>

#include <sys/shm.h>
#include <sys/ipc.h>

#include "shm_vector.h"
#include "shm_semaphore.h"
#include "shm_queue.h"

#include <sys/wait.h>
#include <set>

using namespace std;

#define NUM_CONSUMERS 2

class Producer
{
    shm_queue q_;

public:
    Producer(key_t key) : q_(key)
    {
        cout << "Start producer" << endl;
    }

    void run()
    {
        cout << "Producer run start" << endl;

        for(int i=1; i<1000; i++)
        {
            message_int m;
            memset(&m, 0, sizeof(m));
            m.type = 1;
            m.data = i;

            cout << "Producer " << i << endl;
            q_.enque(&m, sizeof(message_int));
	    
            usleep(300); 	    
        }

        for(int i=0; i<NUM_CONSUMERS; i++)
        {
            message_int m;
            memset(&m, 0, sizeof(m));
            m.type = 1;
            m.data = -1;
            q_.enque(&m, sizeof(message_int));
        }
        cout << "Producer run end" << endl;
    }
};


class Consumer
{
    shm_queue q_;
    shm_vector v_;
    key_t key_;

    int is_prime(int v)
    {
        for(int d=2; d<v; ++d)
            if( v % d == 0)
                return false;

        return true;
    }

public:
    Consumer(key_t key) : q_(key), v_(key, 1024), key_(key)
    {
        cout << "Start consumer" << endl;
    }

    void run()
    {
        cout << "Consumer run start" << endl;


        message_int m;
        do
        {

            memset(&m, 0, sizeof(m));
            m.type = 1;
            m.data = 0;

            q_.deque(&m, sizeof(message_int), m.type);

            if (m.data == -1)
            {
                cout << "Consumer received END " << endl;
                break;
            }

            usleep(200);

            if ( is_prime( m.data ) )
            {
                cout << "is prime " << m.data << endl;

                v_.push_back( m.data );
            }
	    else
            {
                cout << "! " << m.data << endl;
            }

        }
        while( m.data != -1 );

        cout << "Consumer run end" << endl;
        cout.flush();

    }
};

class Printer
{
    shm_vector v_;

public:

    Printer(key_t key) :  v_(key, 1024)
    {
        cout << "Start printer" << endl;
    }

    void run()
    {
        cout << "Primes: " << endl;

        for( int i =0; i< v_.size(); i++)
        {
            cout << v_[i] << ", ";
        }

        cout << endl;
    }
};


int main()
{
    int child_status;
    pid_t pid;

    pid = fork();
    if ( pid == 0 ) // CHILD
    {
        Producer p(0x20);
        cout.flush();
        p.run();
        exit(0);
    }
    else
    {
        cout.flush();
        for(int i=0; i<2; i++)
        {
            pid = fork();
            if ( pid == 0) // CHILD
            {
                Consumer c(0x20);
                cout.flush();

                c.run();
                exit(0);
            }

            cout << "spawned child " << i << " pid:" << pid << endl;
        }

        for(int i=0; i<2; i++)
        {
            cout << "waiting for child " << i << endl;
            cout.flush();

            pid = wait( &child_status );
            cout << "Parent wait stop " << getpid() << " child pid: " << pid << endl;
            cout.flush();
        }

        pid = wait( &child_status ); // Producer child
    }

    Printer p(0x20);
    p.run();

    getchar();
}
