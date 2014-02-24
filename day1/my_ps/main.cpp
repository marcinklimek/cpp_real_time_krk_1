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

    boost::filesystem::directory_iterator it("/proc");
    boost::filesystem::directory_iterator end;

    for( ;it != end; ++it)
    {
        boost::filesystem::path p = it->path();
        num pid = atoi( p.filename().c_str() );

        if( pid )
        {
            p = p / "stat";
            ifstream f( p.string() );

            if ( f.is_open() )
            {
                pid_stat curr;
                f >> curr.pid >> curr.tcomm >> curr.state;
                proc_info[ pid ] = curr;
                f.close();
            }
        }
    }

    for( auto &element : proc_info)
    {
        cout << "PID: " << element.second.pid;
        cout << ", comm " << element.second.tcomm << endl;
    }


    return 0;
}
