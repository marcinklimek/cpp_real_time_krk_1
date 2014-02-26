#include <iostream>
#include <cstdio>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

const int MAX = 5;

int main(int argc, char *argv[ ])
{
    int             f_des, pass = 0;
    pid_t           pid = getpid();
    struct flock    lock;                // for fcntl info

    if (argc < 2)                        // name of file to lock missing
    {
        cerr << "Usage " << *argv << " lock_file_name" << endl;
        return 1;
    }

    sleep(1);                            // don't start immediately

    if ((f_des = open(argv[1], O_RDWR)) < 0)
    {
        perror(argv[1]);                   // could not access file
        return 2;
    }

    lock.l_type   = F_WRLCK;             // set a write lock
    lock.l_whence = 0;                   // start at beginning
    lock.l_start  = 0;                   // with a 0 offset
    lock.l_len    = 0;                   // whole file
    while (fcntl(f_des, F_SETLK, &lock) < 0)
    {
        switch (errno)
        {
        case EAGAIN:
        case EACCES:
            if (++pass < MAX)
                sleep(1);
            else                             // run out of tries
            {
                fcntl(f_des, F_GETLK, &lock);
                cerr << "Process " << pid << " found file "
                     << argv[1] << " locked by " << lock.l_pid << endl;
                return 3;
            }
            continue;
        }
        perror("fcntl");
        return 4;
    }

    cerr << endl << "Process " << pid << " has the file" << endl;
    sleep(10);                           // fake processing
    cerr << "Process " << pid << " is done with the file" << endl;

    return 0;
}

