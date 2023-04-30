#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"


void msgMissingOp(FILE *stream, char *argv[])
{
    fprintf(stderr, "%s: missing operand\nTry '%s --help' for more information.\n",argv[0],argv[0]);
}

void msgErrorTime(FILE *stream, char *argv[])
{
    fprintf(stderr, "%s: invalid time interval\nTry '%s --help' for more information.\n",argv[0], argv[0]);
}

void msgErrorOpenFile(FILE *stream, char *argv[])
{
    fprintf(stderr, "%s: Can't open file for reading\nTry '%s --help' for more information.\n",argv[0], argv[0]);
}

void msgErrOption(FILE *stream, char *argv[])
{
    fprintf(stderr, "%s: invalid option -- '%s'\nTry '%s --help' for more information.\n",argv[0], argv[1], argv[0]);
}


void msgErrCreatFile(FILE *stream, char *argv[])
{
    fprintf(stderr, "%s: Can't create file\nTry '%s --help' for more information.\n",argv[0], argv[0]);
}

void msgErrZiseFileName(FILE *stream, char *argv[], int maxSize)
{
    fprintf(stderr, "%s: he file name can't be greater than %d characters.\n",argv[0], maxSize);
}








int allDigits(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int allHexDigits(const char* str)
{
    size_t len = strlen(str);
    if (len < 3 || str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) {
        return 0;
    }    

    str += 2;
    len -= 2;

    while (*str != '\0')
    {
        if (!isxdigit(*str))
        {
            return 0;
        }
        str++;
        len--;
    }
    return len == 0 ? 1 : 0;
}





/*
    size_t val= strlen(argv[1]);
    printf("\n------------->val = %ld\n", val);  

*/