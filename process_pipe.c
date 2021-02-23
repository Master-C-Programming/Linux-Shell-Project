#include "header.h"

void process_pipe(char **arg, int narg, int how)
{
	int pid[129] = {-1};
	int index_of_pipe[128] = {-1};
	int index = 0;
	
	for(int i = 0; i < narg; i++)
		if(!strcmp(arg[i], "|"))
		{
			index_of_pipe[++index] = i;
			arg[i] = NULL;
		}
	index_of_pipe[++index] = narg;
	
	int p[index - 1][2];
	
	for(int i = 0; i <= index; i++)
	{
		if(i < index)
		{
			pid[i] = fork();
		
			if(pid[i] == 0)
			{
				if(i < (index - 1))		
				{	
					if(pipe(p[i]) < 0)
					{
						perror("pipe() error");
						exit(-1);
					}
				}
				continue;
			}
			else if(pid[i] < 0)
			{
				perror("fork() error");
				exit(-1);
			}
		}
		
		if(i == 0)
			break;
		else
		{
			if(i > 1)
			{
				if(dup2(p[i - 2][0], STDIN_FILENO) < 0)
				{
					perror("dup2() error");
					exit(-1);
				}
				if(close(p[i - 2][0]) < 0)
				{
					perror("close() error");
					exit(-1);
				}
				if(close(p[i - 2][1]) < 0)
				{
					perror("close() error");
					exit(-1);
				}
			}
			
			if(i < index)
			{
				if(dup2(p[i - 1][1], STDOUT_FILENO) < 0)
				{
					perror("dup2() error");
					exit(-1);
				}
				if(close(p[i - 1][0]) < 0)
				{
					perror("close() error");
					exit(-1);
				}
				if(close(p[i - 1][1]) < 0)
				{
					perror("close() error");
					exit(-1);
				}
			}
			
			if(i >= 3)
			{
				for(int j = 0; j < i - 2; j++)
				{
					if(close(p[j][0]) < 0)
					{
						perror("close() error");
						exit(-1);
					}
					if(close(p[j][1]) < 0)
					{
						perror("close() error");
						exit(-1);
					}
				}
			}
			
			if(is_redirection(arg + index_of_pipe[i - 1] + 1, index_of_pipe[i] - index_of_pipe[i - 1] - 1))
			    process_redir(arg + index_of_pipe[i - 1] + 1, index_of_pipe[i] - index_of_pipe[i - 1] - 1);
			else
			{
			    execvp(*(arg + index_of_pipe[i - 1] + 1), arg + index_of_pipe[i - 1] + 1);
			    fprintf(stderr, "%s: command not found\n", *(arg + index_of_pipe[i - 1] + 1));
			    exit(-1);
			}
		}
	}
	
	while (waitpid(pid[index], NULL, 0) < 0)
        if (errno != EINTR) return;
    return;
	/*
	if(how == BACKGROUND)
		;
	else
		;
	*/
}

/*
	pid[0] = fork();
	if(pid[0] == 0)
	{
		pipe(p[0]);
		
		for(int i = 0; i < count; i++)
		{
			pid[i] = fork();
			if(pid[i] == 0)
				continue;
			
			if(i == 0)
				break;
			else
			{
				if(i != (count - 1))
				{
					pipe(p[i]);
					
					dup2(p[i][1], STDOUT_FILENO);
					close(p[i][0]);
					close(p[i][1]);
				}
				
				dup2(p[i - 1][0], STDIN_FILENO);
			    close(p[i - 1][0]);
			    close(p[i - 1][1]);
			    
			    if(is_redirection(comm + index_of_pipe[i] + 1, index_of_pipe[i] - index_of_pipe[i - 1] - 1))
			        process_redir(comm + index_of_pipe[i] + 1, index_of_pipe[i] - index_of_pipe[i - 1] - 1);
			    else
			    {
			        execvp(*(arg + index_of_pipe[i - 1] + 1), arg + index_of_pipe[i - 1] + 1);
			        fprintf(stderr, "%s: command not found\n", second_command[0]);
			        exit(-1);
			    }
			}
		}
		dup2(p[0][1], STDOUT_FILENO);
		close(p[0][0]);
		close(p[0][1]);
		
		if(is_redirection(arg, index_of_pipe[0]))
            process_redir(arg, index_of_pipe[0]);
        else
        {
            execvp(*arg, arg);
            fprintf(stderr, "%s: command not found\n", *arg);
            exit(-1);
        }
	}
	
	
}
*/
