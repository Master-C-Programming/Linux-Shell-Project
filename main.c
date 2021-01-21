#include "header.h"

// int argc : 메인함수에 전달되는 정보의 개수
// char **argv : 메인함수에 전달되는 실직적인 정보(문자열의 배열)
int main(int argc, char **argv, char **env)
{
    char str[1024];

    while (1)
    {
        printf("UOSCS# ");
        fgets(str, sizeof(str) - 1, stdin);
        if (command_line(str) == 0)
            break;
    }

    return 0;
}