#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
//#include "common.h"
#include <stdlib.h>
#include "errno.h"

int s_cat(int argc, char *argv[])
{
    FILE *fd;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int lineCnt = 0;
    int n_cmd = 0;
    char *fPtr = argv[1];

    if(argc != 2)
    {
        if(argc == 3)
        {
            if( memcmp( argv[1], "-n", 2) == 0 && strlen( argv[1]) == 2)
            {
                n_cmd = 1;
                fPtr = argv[2];
            }
            else
            {
                //msgErrOption(stderr, &argv[0]);
                errno = EPERM;
                exit(errno);
            }
        }
        else
        {
            //msgMissingOp(stderr, &argv[0]);
            errno = EPERM;
            exit(errno);
        }
    }


    if( memcmp( fPtr, "--", 2) == 0 )
    {
        if( memcmp( fPtr,"--help", sizeof("--help") ) == 0)
        {
            printf("miniBusyBox v1.0.0 multi-call binary.\n\n");
            printf("Usage: %s [-n] [FILE]\n", argv[0]);
            printf("\n");
            printf("Print FILE to stdout\n");
            printf("\n\t-n	Number output lines\n");
            return 0; 
        }
        errno = EPERM;
        exit(errno);          
    }

    //Open the file in read-only mode and get the file size
    fd = fopen(fPtr, "r");
    if (fd == NULL)
    {
        //msgErrorOpenFile( stderr, argv );
        errno = EPERM;
        exit(errno);
    }
    
    while ((nread = getline(&line, &len, fd)) != -1)
    {
        if( n_cmd )
        {
            printf("     %d ",lineCnt);
        }
        fwrite(line, nread, 1, stdout);
        lineCnt++;
    }
    
    free(line);
    fclose(fd);
    return 0;
}


