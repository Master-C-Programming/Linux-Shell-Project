#include "header.h"

char current_directory[SIZE] = "~";

void change_directory(char** arg, int index)
{
	struct passwd *password;
	char *home;
	char directory_path[SIZE];
	int flag = 0;
	
	password = getpwuid(getuid());
	home = password -> pw_dir;
	
	if(index >= 3)
	{
		printf("cd: too many arguments\n");
	}
	else if(index == 2)
	{
		if(!strncmp("~", arg[1], 2))
			flag = 1;
		if(!strncmp("-", arg[1], 2))
			flag = 2;
		if(!strncmp("~-", arg[1], 3))
			flag = 3;
		if(!strncmp("~/", arg[1], 2))
			flag = 4;
		
		switch(flag)
		{
			case 1 : 
				chdir(home);
				break;
			case 2 :
				printf("%s", previous_directory);
				if(strcmp("\0", previous_directory))
					printf("\n");
			case 3 :
				if(!strcmp("\0", previous_directory))
				{	
					printf("cd: OLDPWD not set\n");
					break;
				}
				else
				{
					chdir(previous_directory);
					break;
				}
			case 4 :
				strcpy(directory_path, home);
				strcat(directory_path, arg[1] + 1);
				if(chdir(directory_path))
					printf("cd: %s: No such file or directory\n", directory_path);
				break;
			default :
				if(chdir(arg[1]))
					printf("cd: %s: No such file or directory\n", arg[1]);
		}
	}
	else 
	{
		chdir(home);
	}
	
	if(!strcmp(current_directory, "~"))
		strcpy(previous_directory, home);
	else
		strcpy(previous_directory, current_directory);
	
	getcwd(current_directory, sizeof(current_directory));
	if(!strcmp(current_directory, home))
		strcpy(current_directory, "~");
	
	return;
}

/*
	~ : HOME (1)
	- : OLDPWD로 이동 (2)
		키자마자 바로하면 cd: OLDPWD not set
	~- : echo 없이 OLDPWD 이동 (3)
	~/[...] : 디렉토리 이동 (4)
	default :  디렉토리 그대로 chdir (0)
	
	마지막에 current_directory와 previous_directory 세팅해 주기
	$HOME 이면 current_directory "~" 변환
 */
 
