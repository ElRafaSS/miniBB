#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "libCat/cat.h"

bool endsWith(char const *in, char const *comp);

int main(int argc, char* argv[])
{
   char *cmd = argv[0];

   // select whether command is on, off, flash or status
   if(endsWith(cmd,"touch"))
   {
//      s_touch( argc, argv );
   }
   else if (endsWith(cmd,"chmod"))
   {
//      s_chmod( argc, argv );
   }
   else if (endsWith(cmd,"sleep"))
   {
//      s_sleep( argc, argv );
   }
   else if ( endsWith(cmd,"cat"))
   {
      s_cat( argc, argv );
   }
   else if ( endsWith(cmd,"rm"))
   {
//      s_rm( argc, argv );
   }
   else
   {
	    printf("Invalid command!\n");
   }

   return 0;
}

bool endsWith(char const *in, char const *comp)
{
   int int_l = strlen(in);
   int comp_l = strlen(comp);
   return (0== strcmp(&in[int_l - comp_l],comp   ));
}
