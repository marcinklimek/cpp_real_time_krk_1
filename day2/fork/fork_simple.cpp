#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"
#include "pid_info.h"

using namespace std;

int main()
{
    pid_t pid;
    cout << " A " << endl;
    cout.flush();
    //pid_info("A");

    pid = fork();  
    if( pid == 0 )
    {
        pid_info("B before");

        cout << " B" << endl; 
        cout.flush();
        sleep(10);

        pid_info("B after");

        return 0;
    }

    pid = fork();
    if ( pid == 0 )
    {
        cout << " C " << endl;
        cout.flush();
    }
}
/*
 A 
 B
 C 

 A 
 B
 C 
 C 

*/