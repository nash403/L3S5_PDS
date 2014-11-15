/* ------------------------------
   $Id: pipe.c,v 1.2 2005/03/29 09:46:52 marquet Exp $
   ------------------------------------------------------------

   mshell - a job manager
   
*/

#include<stdio.h>
#include "pipe.h"
#include "common.h"
#include "unistd.h"

#define STI 0
#define STO 1

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {

  int fds[2];
  int status,i;
  
  for (i = 0; i < nbcmd - 1; i++){
    status = pipe(fds);

    switch(fork())
      {
      case -1:
	unix_error("Error fork");

      case 0:
	close(STI);
	status = dup2(fds[STO],STO);
	if (status < 0)
	  unix_error("Error dup2");
	execvp(cmds[i][0],cmds[i]);
	exit(EXIT_FAILURE);

      default:
	dup2(fds[STI],STI);
      }
  }

  if(!fg)
    waitfg()

  return;
}
