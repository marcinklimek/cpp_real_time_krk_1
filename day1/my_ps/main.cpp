#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <linux/limits.h>
#include <map>
#include <cstdio>

using namespace std;

typedef long long int num;

struct pid_stat
{
    num pid;
    char tcomm[PATH_MAX];
    char state;
};

int main()
{
    map<num, pid_stat> proc_info;

    return 0;
}
