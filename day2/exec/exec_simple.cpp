#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"
#include "wait_info.h"
#include <sched.h>

using namespace std;

//TODO:
// utworzyc proces potomny
// wyswietlic pid nowego procesu
// wyswietlic wartosc statusu

int main( int argc, char *argv[] )
{

    if ( argc > 1 )
    {
        struct sched_param param;
        param.sched_priority = 90;

        pid_t pid = getpid();

        sched_setscheduler( pid, SCHED_FIFO, &param);

        execvp( argv[1], &argv[1] );  // a.out sleep 60

        cout << "return" << endl;
        return 1;
    }

}