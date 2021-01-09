#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <stdbool.h>
#include "header.h"

bool command_line()
{
    char* command=NULL;
    bool is_pipe = false;
    bool is_redirection = false;

    gets(command);
    parsing(command);
    char **arg = token;

    if(!strcmp(arg[0],"quit") || !strcmp(arg[0],"exit"))
        return false;
    else
    {
        if(!strcmp(arg[0],"cd"))
        {
            change_direcory(arg);
            return true;
        }
        is_pipe = is_pipe(arg);
        is_redirection = is_redirection(arg);
        if(is_redirection)
            redirection(arg);
        else if(is_pipe)
            pipe(arg);
        else
            execvp(*arg,arg);
        return true;
    }
}
