#include <sys/types.h>
#include <stdio.h>

main() 
{
  uid_t uid  = getuid();     // rzeczywisty user-id
  uid_t euid = geteuid();    // efektywny user-id
  gid_t gid  = getgid();     // rzeczywisty group-id
  gid_t egid = geteuid();    // efektywny group-id

  pid_t pid  = getpid();
  pid_t ppid = getppid();
  pid_t pgrp = getpgrp();
  pid_t pgid = getpgid(pid);

  printf("UID = %d\t EUID = %d\t GID = %d\t EGID = %d \n",uid, euid, gid, egid);
  printf("PID  = %d\n", pid );
  printf("PPID = %d\n", ppid );
  printf("PGRP = %d\n", pgrp );      
  printf("pgid = %d\n", pgid );
}