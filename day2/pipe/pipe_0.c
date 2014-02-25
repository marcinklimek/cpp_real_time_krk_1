#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 4

char *msg1 = "ABC";
char *msg2 = "DEF";
char *msg3 = "GHI";

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
        memset(inbuf, 0, sizeof(inbuf));
        read(p[0], inbuf, 3);
        printf("%s\n", inbuf);
    }
    exit(0);
}
