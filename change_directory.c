#include "header.h"

void change_directory(char** arg, int index)
{
	struct passwd *password;
	char *home;
	char directory_path[SIZE];
	int flag = 0;
	int home_len = 0;
	
	password = getpwuid(getuid());
	home = password -> pw_dir;
	home_len = strlen(home);
	
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
	
	if(!strncmp(current_directory, "~", 1))
	{
		strcpy(previous_directory, home);
		strcat(previous_directory, current_directory + 1);
	}
	else
		strcpy(previous_directory, current_directory);
	
	getcwd(current_directory, sizeof(current_directory));
	if(!strncmp(current_directory, home, home_len))
	{
		strcpy(directory_path, current_directory);
		strcpy(current_directory, "~");
		strcat(current_directory, directory_path + (home_len));
	}
	
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
 
