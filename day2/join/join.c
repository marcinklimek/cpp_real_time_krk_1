#include <stdio.h>
#include <stdlib.h>

int fatal(char *s)
{
    perror(s);
    exit(1);
}

int join(const char *com1[], const char *com2[])
{
    int p[2], status;


    switch( fork() )
    {
    case -1:  // blad
        fatal("pierwszy fork w join");

    case 0:   // potomek
        break;

    default:  // rodzic
        wait(&status);
        return(status);
    }

    // reszta funkcji wykonywana przez proces potomny

    // utwórz potok
    if(pipe(p) == -1)
        fatal("pipe w join");

    // kolejny potomek 'wnuk'
    switch(fork())
    {
    case -1:
        fatal("drugi fork w join");

    case 0:   // potomek

        // proces zapisu
        dup2(p[1], 1);

        // zamykamy deskryptory
        close(p[0]);
        close(p[1]);

        execvp(com1[0], com1);

        // blad
        fatal("pierwsze wywolanie execvp w join");

    default:
        // proces odczytu
        dup2(p[0], 0); // podlacz stdin do potoku

        // zamykamy deskryptory
        close(p[0]);
        close(p[1]);

        execvp(com2[0], com2);
        fatal("drugie wywolanie execvp w join");
    }
}


main()
{
    const char *one[] = {"ps", "ax", NULL};
    const char *two[] = {"sort", "-g", NULL};
    int ret;

    ret = join(one, two);

    printf("join: %d\n",ret);
    exit(0);
}
