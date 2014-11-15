/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "forkfork.h"

void forkfork(func_t f, void *arg){
  switch(fork())
    {
    case -1:
      fprintf(stderr,"erreur création processus.\n");
      exit(EXIT_FAILURE);
    case 0:
      switch(fork())
	{
	case -1:
	  fprintf(stderr,"erreur création processus.\n");
	  exit(EXIT_FAILURE);
	case 0:
	  f(arg);
	  exit(EXIT_SUCCESS);
	default :
	  exit(EXIT_SUCCESS);
	}
    default:
      wait(NULL);
      exit(EXIT_SUCCESS);
    }
}
