#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"
#include "wait_info.h"

using namespace std;

int main()
{
    int status;
    int value = 10;

    pid_t pid;
    cout << " A " << endl;
    cout.flush();

    pid = fork();  
    if( pid == 0 )
    {
        cout << " B" << endl; 
        cout.flush();
        sleep(10);

        cout << value << endl;

        return 1;
    }

    while( waitpid(pid, &status, WNOHANG) == 0 )
    {
        cout << ".. wait" << endl;
        sleep(1);
    }

    wait_info(pid, status);

}
