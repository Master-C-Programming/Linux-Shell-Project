#include "header.h"

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