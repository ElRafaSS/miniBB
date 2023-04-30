#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "common.h"
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include "rm.h"


int s_rm(int argc, char *argv[])
{
    int n_cmd = 0;
    char *fPtr = argv[1];
    struct stat st;
    struct dirent *entry;

    if(argc != 2)
    {
        if(argc == 3)
        {
            if( memcmp( argv[1], "-r", 2) == 0 && strlen( argv[1]) == 2)
            {
                fPtr = argv[2];
                
                if (stat(fPtr, &st) == -1)
                {
                    perror("stat");
                    errno = EPERM;
                    exit(errno);
                }
                
                if (S_ISDIR(st.st_mode))
                {
                    n_cmd = 2;
                } else
                {
                    n_cmd = 1;
                } 
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


    if( n_cmd == 0 || n_cmd == 1 )
    {
        if ( unlink(fPtr) == -1 )//Remove the specified file
        {
            perror("Can't remove file");
            errno = EPERM;
            exit(errno);
        }   
    }
    else if( n_cmd = 2 )//File
    {
        if ( rmdir(fPtr) == -1 )//Remove the specified directory
        {
            if (rmDirectory(fPtr) != 0)
            {
                fprintf(stderr, "Error removing directory %s.\n", fPtr);
                errno = EPERM;
                exit(errno);
            }

            printf("%s removed successfully.\n", fPtr);
        }          
    }   


    return 0;
}



int rmDirectory(const char *dir_path)
{
    static int recCnt= 0;

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        errno = EPERM;
        exit(errno);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        recCnt++;
        char subPath[500];

        if( recCnt > 50)
        {
            perror("\nCould not delete all.");
            closedir(dir);
            errno = EPERM;
            exit(errno);
        }

        //If this is a directory (Type of file; not supported by all filesystem types)       
        if (entry->d_type == DT_DIR)
        {
            // Skip "." and ".." directories
            if (memcmp(entry->d_name, ".",1) == 0 || memcmp(entry->d_name, "..",2) == 0)
            {
                continue;
            }
            // Recursively remove subdirectory
            snprintf(subPath, sizeof(subPath), "%s/%s", dir_path, entry->d_name);
            if (rmDirectory(subPath) != 0)
            {
                closedir(dir);
                errno = EPERM;
                exit(errno);
            }
        }
        else//If this is a file
        {
            // Remove regular file
            snprintf(subPath, sizeof(subPath), "%s/%s", dir_path, entry->d_name);
            if (unlink(subPath) != 0)
            {
                perror("unlink");
                closedir(dir);
                errno = EPERM;
                exit(errno);
            }
        }
    }

    if (rmdir(dir_path) != 0)
    {
        perror("rmdir");
        closedir(dir);
        errno = EPERM;
        exit(errno);
    }

    closedir(dir);
    return 0;
}