#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "wait_info.h"

using namespace std;
using namespace boost;

int exec(vector<string> arguments)
{
    // execvp non-const
    std::vector<char*> argv;

    for ( auto element : arguments)
        argv.push_back( const_cast<char*>(element.c_str()) );

    argv.push_back(NULL);

    pid_t child;
    int status;

    child = fork();
    if ( child == 0) 
    {
        execvp(argv[0], &argv[0] );
        cout << "error" <<endl;
        return -1;
    }

    
    cout << "Child PID: " << child << endl << endl;

    waitpid(child, &status, 0);

    cout << endl;
    wait_info(child, status);


    return status;
}

int main()
{
    while(cin)
    {
        // prompt
        cout << "$ ";

        // command
        string command;
        getline(cin, command);

        if(command == "exit")
            break;

        vector<string> arguments;

        boost::char_separator<char> sep(" ");
        tokenizer< boost::char_separator<char> > tok(command, sep);

        for ( auto element : tok)
            arguments.push_back( element.c_str() );

        exec( arguments );
    }
}
