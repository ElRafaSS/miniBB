#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <time.h>
#include "common.h"
#include "touch.h"

#define MAX_LENGTH 51

int s_touch(int argc, char *argv[])
{
    char filename[MAX_LENGTH] = { 0 };
    char *fPtr = argv[1];
    int n_cmd = 0;
    struct utimbuf newTimes;
    time_t seconds = 0;

    if(argc != 2)
    {
        if(argc == 4)
        {
            if( memcmp( argv[1], "-t", 2) == 0 && strlen( argv[1]) == 2)
            {
                msgErrOption(stderr, &argv[0]);
                n_cmd = 1;
                fPtr = argv[3];
            }
            else
            {
                msgErrOption(stderr, &argv[0]);
                errno = EPERM;
                exit(errno);
            }
        }
        else
        {
            msgMissingOp(stderr, &argv[0]);
            errno = EPERM;
            exit(errno);
        }
    }









    if( strlen( fPtr) > (MAX_LENGTH-1) )
    {
        msgErrZiseFileName(stderr, argv, (MAX_LENGTH-1));
        errno = EPERM;
        exit(errno);
    }




    strncat(filename, fPtr, sizeof(filename)-1);

    if( memcmp( filename,"--", 2 ) == 0)
    {
        if( memcmp( &filename[2],"help", sizeof("help") ) == 0)
        {
            printf("miniBusyBox v1.0.0 multi-call binary.\n\n");
            printf("Usage: touch FILE\n");
            printf("Update the access and modification times of each FILE to the current time.\n");
            printf("\n");
            printf("--help     display this help and exit\n");
            return 0; 
        }
        msgMissingOp(stderr, argv);
        errno = EPERM;
        exit(errno);          
    }




    if( filename[0] == '-' && filename[1] != '-' )
    {
        return 0;
    }


    
    //The access and modification times of the file are set.
    if( n_cmd )
    {
        const char *file_path = fPtr;
        struct stat file_stat;

        FILE *fp = fopen(file_path, "a");
        if (fp == NULL)
        {
            perror("Failed to open file");
            errno = EPERM;
            exit(errno);
        }
        fclose(fp); // Close the file        

        if ( stat(file_path, &file_stat) < 0 )
        {
            perror("Failed to stat file");
            errno = EPERM;
            exit(errno);
        }
        
        newTimes.actime = file_stat.st_atime; // Use the original access time



        seconds = atoi( argv[2] );
        newTimes.modtime = seconds; // Use the current time as the new modification time
    }
    else
    {
        newTimes.modtime = time(NULL);
    }


    if ( utime(filename, &newTimes) == -1 )
    {
        //If pathname does not exist,create it. ENOENT (short for Error No Entry).
        if (errno == ENOENT)
        {
            if ( creat(filename, 00664) == -1 )
            {
                msgErrCreatFile( stderr, argv);
                errno = EPERM;
                exit(errno);
            }
        }
        /* If we can't update the timestamp,
        something is wrong */
        else
        {
            perror("Can't update timestamp");
            errno = EPERM;
            exit(errno);
        }
    }
    else
    {
        //printf("\n--->");
    }
    return 0;
}
