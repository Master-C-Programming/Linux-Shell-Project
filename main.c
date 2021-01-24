#include "header.h"

char current_directory[SIZE];

int main(int argc, char **argv)
{	
    while (1)
    {
        printf("UOSCS:%s# ", current_directory);
        if (!command_line())
            break;
    }

    return 0;
}
