/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "makeargv.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <getopt.h> 
#include <string.h>
#include <signal.h>

static int opt_and = 0;
static int opt_or = 0;
static int opt_cc = 0;
static int opt_kill = 0;


static const struct option long_options[] = {
  { "and", no_argument, &opt_and, 1 },
  { "or", no_argument, &opt_or, 1 },
  { "cc", no_argument, &opt_cc, 1 },
  { "kill", no_argument, &opt_kill, 1 },
  { NULL, no_argument, NULL, 0 }
};


int main (int argc, char *argv[])
{
  int i,status;
  int res = 1;
  int option_counter = 0;
  pid_t pid;

  if (argc < 2){
    perror("Illegal Argument.\nUsage :\n\t ./do [--and|--or] cmd ...\n");
    exit(EXIT_FAILURE);
  }

  printf("i'm the father %d\n",getpid());
  /* récupérer les options positionnées */
  while((status = getopt_long(argc,argv,"",long_options,NULL)) != -1);
  printf("and%d\tor%d\tcc%d\tkill%d\n",opt_and,opt_or,opt_cc,opt_kill);

  /* erreur si and et or sont positionnées à deux */
  if (!((opt_or && !opt_and) || (opt_and && !opt_or) || (!opt_or && !opt_and))){
    fprintf(stderr,"Ambigous argument. Option --and should be used separately with option --or\n");
    exit(EXIT_FAILURE);
  }

  /* warning si kill est positionée sans cc */
  if (opt_kill && !opt_cc)
    fprintf(stderr,"Warning : option --kill must be used with option --cc otherwise it is ignored\n");

  /* on compte le nombre d'options positionnées */
  if ((opt_or && !opt_and) || (opt_and && !opt_or))    /* or ou and est positionné, pas les deux*/
    option_counter++;
  if (opt_cc)
    option_counter++;
  if (opt_cc && opt_kill)
    option_counter++;

  printf("%d option positionned\n",option_counter);

  /* traiter argv[i] */
  for (i = option_counter+1; i < argc; i++ ) { 
    char **cmdargv; 
    makeargv(argv[i], " \t", &cmdargv);
    switch(fork())
      {
      case -1 : 
	perror("Erreur fork\n");
	exit(EXIT_FAILURE);
      case 0:
	printf("i'm a son %d\n",getpid());
	execvp(cmdargv[0], cmdargv);
	exit(EXIT_FAILURE);  /* si execvp ne marche pas */
      default:
	freeargv(cmdargv);
      }
  }

  /* on attends les fils et on traite selon option */
  for (i = option_counter+1; i < argc; i++ ) {
    pid = wait(&status);
    printf("i'm son %d and i just finished\n",pid);

    if((opt_and && !opt_or) || (!opt_and && !opt_or)){ /*or n'est pas positionnée ou and est positionnée */
      if (WEXITSTATUS(status) == 0)
	res *= 1;
      else {
	res *= 0;
	if (opt_cc){ /* si cc est positonnée */
	  if (opt_kill){ /* si kill est positionnée on tue les fils restants*/
	    while ((pid = wait(&status)) != -1){
	      kill(pid,SIGKILL);
	    }
	    printf("%d\n",res);
	    return res;
	  }
	  printf("%d\n",res);
	  return res;
	}
      }
    }

    if (opt_or){ /* or est positionnée */
      res = 0;
      if (WEXITSTATUS(status) == 0){
	res = 1;
	if (opt_cc){ /* si cc est positionnée */
	  if (opt_kill){ /* si kill est positionnée on tue les fils restants*/
	    while ((pid = wait(&status)) != -1){
	      kill(pid,SIGKILL);
	    }
	    printf("%d\n",res);  
	    return res;
	  }
	  printf("%d\n",res);
	  return res;
	} 
      }
    }


  }
  printf("%d\n",res);
  return res;
}		




