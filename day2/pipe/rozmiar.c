#include <signal.h>
#include <unistd.h>
#include <limits.h>

int count;

void alrm_action(int signo)
{
    printf("Zapis zablokowany po %d znakach\n", count);
    exit(0);
}

main()
{
    int p[2];
    int pipe_size;
    char c = 'x';

    static struct sigaction act;

    act.sa_handler = alrm_action;
    sigfillset(&(act.sa_mask));

    // utworz potok
    if(pipe(p) == -1)
    {
        perror("wywolanie pipe");
        exit(1);
    }

    // rozmiar potoku
    pipe_size = fpathconf(p[0], _PC_PIPE_BUF);
    printf("Maksymalny rozmiar potoku: %d\n", pipe_size);

    // przyklad uzycia ALARM
    sigaction(SIGALRM, &act, NULL);

    while(1)
    {
        // ustaw alarm
        alarm(10);

        // zapisz do potoku
        write(p[1], &c, 1);

        // wylacz alarm
        alarm(0);

        if((++count % 1024) == 0)
            printf("%d znakow w potoku\n", count);
    }
}

