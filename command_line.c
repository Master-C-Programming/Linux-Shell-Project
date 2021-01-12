#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "header.h"

bool command_line()
{
    char *arg[1024];
    bool is_pipe = false;
    bool is_redirection = false;
    int type = 0;
    int index = 0;

    fgets(input, 1024, stdin);
    tok = tokens;
    ptr = input;
    type = get_token(&arg[index++]);
    if (type == 2)
    {
        while (type == 2)
            type = get_token(&arg[index++]);
    }

    if (type == 1)
    {
        if (!strcmp(arg[0], "quit") || !strcmp(arg[0], "exit"))
            return false;
        else
        {
            if (!strcmp(arg[0], "cd"))
            {
                change_directory(arg);
                return true;
            }
            is_pipe = is_pipe(arg);
            is_redirection = is_redirection(arg);
            if (is_redirection)
                redirection(arg);
            else if (is_pipe)
                pipe(arg);
            else
                execvp(*arg, arg);
            return true;
        }
    }
    // EMPERSAND의 경우 
    // 아직 구현을 하지 않았습니다.
    if(type == 0)
    {
        return true;
    }
}
