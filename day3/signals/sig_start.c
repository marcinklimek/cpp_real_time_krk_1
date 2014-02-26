#include <signal.h>
#include <stdio.h>
#include "../inc/misc_functions.h"

void catch_int(int signum)
{
    printf("Handler %d\n", signum);
}


int main(int argc, char const *argv[])
{
    int i;
    static struct sigaction action;
    static struct sigaction old_action;
    sigset_t set1, set2;


    action.sa_handler = catch_int;
    sigaction( SIGINT, &action, &old_action);


    sigfillset( &set1 );

    sigfillset( &set2 );
    sigdelset( &set2, SIGINT );   

    // sekcja krytyczna
    sigprocmask( SIG_SETMASK, &set1, NULL);
    
    printf("Sekcja krytyczna\n");

    raise( SIGINT );

    printf("Po sekcji krytycznej\n");
    sigprocmask( SIG_SETMASK, &set2, NULL);
    //raise( SIGINT );

    printf("KONIEC\n");


    for( i=0; i<30; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
   
    return 0;
}
