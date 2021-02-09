#include "header.h"

int cnt;
int current_cnt;
int largest_num;
char command[512];
char current_command[512];

void handle_signal (int sig)
{
    cnt = cnt - 1;
}

void background(char **arg, int index)
{
    
    if(cnt==0)
    {
        current_cnt = ++cnt;
        largest_num = current_cnt;
    }
    else
    {
        current_cnt = ++largest_num;
        ++cnt;
    }

    memset(command,0,sizeof(command));
    for(int i = 0 ; i < index ; i++)
    {
        strcat(command,arg[i]);
        strcat(command," ");
    }
    strcpy(current_command,command);

    
    int ppid = getpid();
    int pid1 = fork();
    int pstatus = 0;
    int ppstatus = 0;
   
    signal(SIGUSR1,handle_signal);

    if(pid1==0)
    {
        int pid2 = fork();
        if(pid2==0)
        {
            execvp(*arg,arg);
        }
        else
        {
            printf("\n[%d] %d\n",current_cnt,pid2);
            waitpid(pid2,&pstatus,WUNTRACED);
            kill(ppid,SIGUSR1);
            printf("[%d]  Done \t\t\t %s\n",current_cnt,current_command);
            kill(getpid(),SIGKILL);
        }       
    }
    else
    {
        waitpid(pid1,&ppstatus,WNOHANG);
    }

}