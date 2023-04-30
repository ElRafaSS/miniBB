#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"
#include "sleep.h"
#include <errno.h>


int s_sleep(int argc, char *argv[])
{
    long int time_s = 0;
    
    /* Check that the user supplied two arguments */
    if(argc != 2)
    {
        if(argc > 2)
        {
            msgErrorTime(stderr, argv);
        }
        else
        {
            msgMissingOp(stderr, argv);
        }
        errno = EPERM;
        exit(errno);
    }

    if( memcmp( argv[1], "--", 2) == 0 )
    {
        if( memcmp( argv[1],"--help", sizeof("--help") ) == 0)
        {
            printf("miniBusyBox v1.0.0 multi-call binary.\n\n");
            printf("Usage: sleep [Integer value in seconds]\n");
            printf("\n");
            printf("Pause for a time in seconds equal to the total of the arg given.\n");
            return 0; 
        }
        errno = EPERM;
        exit(errno);           
    }


    if( allHexDigits(argv[1]) )
    {
        time_s = strtol(argv[1], NULL, 16);
    }
    else if( allDigits(argv[1]) )
    {
        time_s = atoi( argv[1] );
    }
    else
    {
        msgErrorTime(stderr, argv);
        errno = EPERM;
        exit(errno);
    }


    sleep( (unsigned int )time_s );
    
    exit(errno);
}




