#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "../inc/misc_functions.h"

sig_atomic_t sigusr1_count = 0;
sig_atomic_t alarmed = 0;
int seconds_h = 1;

void handler (int signal_number)
{
  wrout("handler\n");
  ++sigusr1_count;
}

static void sighandler( int signum )
{   
  alarmed = 1;
  wrout("AAA\n");
  alarm( seconds_h );
}

void set_alarm( int seconds )
{
  alarmed = 0;
  signal( SIGALRM, sighandler );
  alarm( seconds );
  seconds_h = seconds;
}

main() 
{
  set_alarm(1);

  getchar();
}
