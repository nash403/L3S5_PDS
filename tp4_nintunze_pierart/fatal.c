/*
NOM : NINTUNZE Honoré
DATE : 02/02/2014
*/
#include <stdio.h>
#include <stdlib.h>

extern void fatal (int assert, const char *message, int status)
{
  if (assert)
    {
      int i;
      for (i=0 ; message[i] ; i++)
	{
	  if (message[i] == '\0') break ;
	  putchar(message[i]) ;
	}
      exit (status) ;
    }
  return ;
}
