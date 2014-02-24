#include <string.h>
#include <stdio.h>
#include <sys/utsname.h>

int main(int argc, char **argv)
{
    struct utsname u;
    int crit1, crit2 = 0;
    FILE *fd;

    uname(&u);
    crit1 = strcasestr (u.version, "PREEMPT RT");

    if ((fd = fopen("/sys/kernel/realtime","r")) != NULL) {
        int flag;
        crit2 = ((fscanf(fd, "%d", &flag) == 1) && (flag == 1));
        fclose(fd);
    }
    fprintf(stderr, "this is a %s kernel\n",
            (crit1 && crit2)  ? "PREEMPT RT" : "vanilla");
}
