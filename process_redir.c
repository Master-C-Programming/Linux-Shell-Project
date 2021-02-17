#include "header.h"

void process_redir(char **arg, int narg)
{
	char *exec_arg[SIZE];
	char *redir_arg[SIZE];
	int exec_index = 0;
	int redir_index = 0;
	int fd;
	int flag = 1;
	
	// arg에서 exec할 구문을 분리
	for(int i = 0; i <= narg; i++)
	{
		// NULL을 만나면 중단(파이프 별로 리디렉션하기 위함)
		if(!arg[i])
		{
			*(exec_arg + exec_index) = NULL;
			*(redir_arg + redir_index) = NULL;
			break;
		}
		else if(!strncmp("<", arg[i], 2) || !strncmp(">", arg[i], 2) || !strncmp(">>", arg[i], 3))
		{
			// < > >> 저장
			*(redir_arg + redir_index++) = *(arg + i++);
			// < > >> 뒷 리디렉션 대상 구문 저장
			*(redir_arg + redir_index++) = *(arg + i);
		}
		else // 실행할 구문 저장
			*(exec_arg + exec_index++) = *(arg + i);
	}
	
	redir_index = 0;
	
	while(flag)
	{
		// < > >> 에 따라 수행할 동작 flag로 설정
		if(!redir_arg[redir_index])
			flag = 0;
		else if(!strncmp("<", redir_arg[redir_index], 2))
			flag = 1;
		else if(!strncmp(">", redir_arg[redir_index], 2))
			flag = 2;
		else if(!strncmp(">>", redir_arg[redir_index], 3))
			flag = 3;
		else
			flag = 0;
		
		// < > >> 다음 명령어를 읽기
		redir_index++;
		
		// 리디렉션 수행
		switch(flag)
		{
			case 1 :
				fd = open(redir_arg[redir_index++], O_RDONLY, 0644);
				if (fd < 0) 
				{
					perror("open() error");
					exit(-1);
				}
				else
				{
					if(dup2(fd, STDIN_FILENO) < 0)
					{
						perror("dup2() error");
						exit(-1);
					}
					if(close(fd) < 0)
					{
						perror("close() error");
						exit(-1);
					}
				}
				break;
			case 2 :
				fd = open(redir_arg[redir_index++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0) 
				{
					perror("open() error");
					exit(-1);
				}
				else
				{
					if(dup2(fd, STDOUT_FILENO) < 0)
					{
						perror("dup2() error");
						exit(-1);
					}
					if(close(fd) < 0)
					{
						perror("close() error");
						exit(-1);
					}
				}
				break;
			case 3 :
				fd = open(redir_arg[redir_index++], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0) 
				{
					perror("open() error");
					exit(-1);
				}
				else
				{
					if(dup2(fd, STDOUT_FILENO) < 0)
					{
						perror("dup2() error");
						exit(-1);
					}
					if(close(fd) < 0)
					{
						perror("close() error");
						exit(-1);
					}
				}
				break;
			default :
				flag = 0;
		}
	}

	execvp(*exec_arg, exec_arg);
	
	// 커맨드가 없으면 실행 안 함, 실행에 실패하면 에러 메세지
	if(*exec_arg)
	{
		fprintf(stderr, "Command '%s' not found.\n", *exec_arg);
		exit(-1);
	}
	
	return;
}
