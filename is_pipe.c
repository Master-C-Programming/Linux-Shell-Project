#include "header.h"

bool is_pipe(char **arg, int size)
{
	bool result = false;
	
	for(int i = 0; i < size; i++)
		if(!strcmp(arg[i], "|"))
		{
			result = true;
			break;
		}
	
	return result;
}
			
