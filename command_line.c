#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "header.h"

bool command_line(void)
{
    char *string = NULL;
    int is_pipe = 0;
    int is_redirection = 0;
    char **arg = NULL;

    while(1)
    {
        printf("#shell: ");
        gets(string);
        parse(string);
        arg = token;
        if(!strcmp(arg[0],"quit") || !strcmp(arg[0],"exit"))
            break;
        else
        {
            if(!strcmp(token[0],"cd"))
                change_directory(arg);
            
            is_pipe=is_pipe(arg);
            is_redirection=is_redirection(arg);
            if(is_redirection)
                redirection(arg);
            else if(is_pipe)
                pipe(token);
            else
                execvp(*arg,arg);
        }
    }
    return false;
}