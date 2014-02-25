#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"
#include "wait_info.h"

using namespace std;

int main()
{
    int status;

    pid_t pid;
    cout << " A " << endl;
    cout.flush();

    pid = fork();  
    if( pid == 0 )
    {
        cout << " B" << endl; 
        cout.flush();
        sleep(10);

        return 1;
    }


    pid_t chld_pid = wait(&status);

    wait_info( chld_pid, status );


}
