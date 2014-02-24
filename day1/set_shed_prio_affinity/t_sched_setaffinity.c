
void set_affinity()
{
    pid_t pid;
    cpu_set_t set;
    int cpu;
    unsigned long mask;


    CPU_ZERO(&set);

    for (cpu = 0; mask > 0; cpu++, mask >>= 1)
        if (mask & 1)
            CPU_SET(cpu, &set);

    if (sched_setaffinity(pid, sizeof(set), &set) == -1)
        errExit("sched_setaffinity");

}
