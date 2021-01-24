#include "header.h"

int get_token(char **arg)
{
    // token 타입 저장
    int type = ARG;
    // token 시작 주소 arg로 넘겨주기
    *arg = tok;

    // whitespace 뛰어넘기
    while((*ptr == ' ') || (*ptr == '\t'))
        ptr++;

    switch(*tok++ = *ptr++)
    {
        case '&':
            type = AMPERSAND;
            break;
        case '\n':
            type = EOL;
            break;
        default:
            while((*ptr != ' ') && (*ptr != '\t') && (*ptr != '&') && (*ptr != '\n'))
                *tok++ = *ptr++;
            break;
    }
    *tok++ = '\0';

    return type;
}
