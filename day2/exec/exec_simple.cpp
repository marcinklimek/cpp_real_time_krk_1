#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"
#include "wait_info.h"
#include <sched.h>

using namespace std;

int main( int arc, char *argv[] )
{

    if ( argc > 1 )
    {


        execvp( argv[1], &argv[1] );

        cout << "error" << endl;
        return 1;
    }

}