#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn (char* program, char** arg_list)
{
  pid_t child_pid;

  child_pid = fork ();

  if (child_pid != 0)
    return child_pid;
  else 
  {
    
    execvp (program, arg_list);
    
    //error
    fprintf(stderr, "an error occurred in execvp\n");
    abort ();
  }
}

int main ()
{
  pid_t child_pid_spawn;
  pid_t child_pid_wait;
  int status;

  char* arg_list[] = {
    "ls",     /* argv[0] */
    "-l", 
    "/",
    NULL      /* wymagane zakonczenie  */
  };

  child_pid_spawn = spawn ("ls", arg_list); 
  printf ("wait..\n");

  child_pid_wait = wait(&status);
  printf("post wait child_pid_spawn: %d, child_pid_wait: %d\n", child_pid_spawn, child_pid_wait);

  return 0;
}
