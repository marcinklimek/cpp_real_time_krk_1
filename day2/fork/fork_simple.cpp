#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include "unistd.h"

using namespace std;

int main()
{
    cout << " A " << endl;

    fork();  cout.flush();
    cout << " B" << endl; 
    cout.flush();

    fork();
    cout << " C " << endl;
    cout.flush();

}
