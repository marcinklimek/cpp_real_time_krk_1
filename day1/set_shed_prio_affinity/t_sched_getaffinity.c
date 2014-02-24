void get_affinity()
{
    pid_t pid;
    cpu_set_t set;
    size_t s;
    int cpu;

    s = sched_getaffinity(pid, sizeof(cpu_set_t), &set);
    if (s == -1)
        errExit("sched_getaffinity");

    printf("CPUs:");
    for (cpu = 0; cpu < CPU_SETSIZE; cpu++)
        if (CPU_ISSET(cpu, &set))
            printf(" %d", cpu);
    printf("\n");
}
