#ifndef __PID_INFO__
#define __PID_INFO__

#include <sys/types.h>
#include <stdio.h>

void pid_info(char* who) 
{
  uid_t uid  = getuid();     // rzeczywisty user-id
  uid_t euid = geteuid();    // efektywny user-id
  gid_t gid  = getgid();     // rzeczywisty group-id
  gid_t egid = geteuid();    // efektywny group-id

  pid_t pid  = getpid();
  pid_t ppid = getppid();
  pid_t pgrp = getpgrp();
  pid_t pgid = getpgid(pid);

  
  printf("[%s] UID = %d\t EUID = %d\t GID = %d\t EGID = %d \n",who, uid, euid, gid, egid);
  printf("[%s] PID  = %d\t", who, pid );
  printf(" PPID = %d\t", ppid );
  printf(" PGRP = %d\t", pgrp );      
  printf(" PGID = %d\n", pgid );
}

#endif /* __PID_INFO__ */
