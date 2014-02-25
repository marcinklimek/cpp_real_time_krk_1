#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const int MAX    =256;
const int CMD_MAX=10;

char cmds[] = " ls  ps  df ";

int main( )
{
    char *valid_cmds = cmds;
    char  line_input[MAX], the_cmd[CMD_MAX];
    char  *new_args[CMD_MAX], *cp;
    int   i;

    while (1)
    {
        cout << "cmd> ";
        if (cin.getline(line_input, MAX, '\n') != NULL)
        {
            cp = line_input;
            i  = 0;

            if ((new_args[i] = strtok(cp, " ")) != NULL)
            {
                strcpy(the_cmd, new_args[i]);
                strcat(the_cmd, " ");

                if ((strstr(valid_cmds, the_cmd) - valid_cmds) % 4 == 1)
                {
                    do
                    {
                        cp = NULL;
                        new_args[++i] = strtok(cp, " ");
                    }
                    while (i < CMD_MAX && new_args[i] != NULL);

                    new_args[i] = NULL;

                    switch (fork( ))
                    {
                    case 0:
                        execvp(new_args[0], new_args);
                        perror("exec failure");
                        exit(1);
                    case -1:
                        perror("fork failure");
                        exit(2);
                    default:
                        // In the parent we should be waiting for
                        // the child to finish
                        ;
                    }
                }
                else
                    cout << "?" << endl;
            }
        }
    }
}
