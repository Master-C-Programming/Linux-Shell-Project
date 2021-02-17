#include "header.h"

int main(int argc, char **argv)
{	
    struct passwd *password;
	char *home;
	char temp[SIZE];
	int home_len = 0;
	
	password = getpwuid(getuid());
	home = password -> pw_dir;
	home_len = strlen(home);
	
	getcwd(current_directory, sizeof(current_directory));
	if(!strncmp(current_directory, home, home_len))
	{
		strcpy(temp, current_directory);
		strcpy(current_directory, "~");
		strcat(current_directory, temp + (home_len));
	}

    while (1)
    {
        printf("UOSCS:%s# ", current_directory);
        if (!command_line())
            break;
    }

    return 0;
}
