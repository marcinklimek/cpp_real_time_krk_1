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

    // piszemy do potoku
    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);

    // odczytujemy z potoku
    for(j = 0; j < 3; j++)
    {
        read(p[0], inbuf, MSGSIZE);
        printf("%s\n", inbuf);
    }
    exit(0);
}
