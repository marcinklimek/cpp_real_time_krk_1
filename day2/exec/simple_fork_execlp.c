#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main( )
{

    execlp("/bin/echo", "echo", "abc", "ABC", "123", NULL);

}
