#include "header.h"

bool is_redirection(char **arg, int size)
{
	bool result = false;
	
	for(int i = 0; i < size; i++)
		if(!strcmp(arg[i], "<") || !strcmp(arg[i], ">") || !strncmp(arg[i], ">>", 3))
		{
			result = true;
			break;
		}
	
	return result;
}
			
