#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

main()
{
    char inbuf[MSGSIZE];
    int p[2], j;

    // otwieramy potok
    if(pipe(p) == -1)
    {
        perror("utworzenie potoku");
        exit(1);
    }

    // 0 - stdin
    // 1 - stdout
    // 2 - stderr
    // 3 - p[0] - pipe in
    // 4 - p[1] - pipe out

    pid_t pid = fork();

    if (pid == 0)
    {
        close( p[0] );
        // piszemy do potoku
        write(p[1], msg1, MSGSIZE);
        sleep(2);
        write(p[1], msg2, MSGSIZE);
        sleep(2);
        write(p[1], msg3, MSGSIZE);
    }
    else
    {
        close( p[1] );

        // odczytujemy z potoku
        for(j = 0; j < 3; j++)
        {
            read(p[0], inbuf, MSGSIZE);
            printf("%s\n", inbuf);
        }
    }
}
