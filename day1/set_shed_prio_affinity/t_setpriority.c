
void set_get_prio()
{
    int which;
    int prio;
    id_t who;

    if (setpriority(which, who, prio) == -1)
        errExit("setpriority");

    errno = 0;                  
    prio = getpriority(which, who);
    if (prio == -1 && errno != 0)
        errExit("getpriority");

    printf("Nice value = %d\n", prio);

}
