#include "header.h"

void fork_and_call_process_redir(char **arg, int narg)
{
	int pid;
	
	if((pid = fork()) < 0)
	{
		perror("fork() error");
		exit(-1);
	}
	else if(pid == 0) // 자식 프로세스
		process_redir(arg, narg);
	
	// 부모 프로세스 대기
	waitpid(pid, NULL, 0);
	
	return;
}