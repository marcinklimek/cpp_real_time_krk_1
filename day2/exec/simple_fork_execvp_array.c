#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  char* arg_list[] = {
    "ls",     /* argv[0] */
    "-l", 
    "/",
    NULL      /* wymagane zakonczenie  */
  };

  execvp (arg_list[0], arg_list);

  return 0;
}
