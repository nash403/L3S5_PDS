/* ------------------------------
   $Id: sighandlers.c,v 1.1 2005/03/17 13:00:46 marquet Exp $
   ------------------------------------------------------------

   mshell - a job manager
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#include "jobs.h"
#include "common.h"
#include "sighandlers.h"


/*
 * Signal - wrapper for the sigaction function
 */
int
signal_wrapper(int signum, handler_t *handler) 
{
  /*define the action*/
  struct sigaction action;
  
  action.sa_handler = handler;
  
  if (sigemptyset(&action.sa_mask) < 0)
    unix_error("sigempty error");
 
  action.sa_flags = SA_RESTART;

  /*associate the action to the signal*/
  sigaction(signum,&action,NULL);

  return 1;
}


/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children
 */
void
sigchld_handler(int sig) 
{
  pid_t pid;
  int status;
  struct job_t *job;
      
  if (verbose)
    printf("sigchld_handler: entering\n");
    
  

  while ((pid = waitpid(-1,&status,WUNTRACED)) > 0){

    job = jobs_getjobpid(pid);

    if (WIFEXITED(status)){ /*if job exited normally*/
     
      printf("[%d] (%d) Terminated \t\t %s\n",job->jb_jid,pid,job->jb_cmdline);
      if(!jobs_deletejob(pid)) /* delete the job */
      	unix_error("error while deleting job");

    } else if (WIFSTOPPED(status)){/*if job received a stop signal*/
      
      job->jb_state = ST; /* change the job state */
      printf("[%d] (%d) Suspended \t\t %s\n",job->jb_jid,pid,job->jb_cmdline);

    } else if (WIFSIGNALED(status)){/*if job was killed*/
      
      printf("[%d] (%d) Killed \t\t %s\n",job->jb_jid,pid,job->jb_cmdline);
      if(!jobs_deletejob(pid)) /* delete the job */
      	unix_error("error while deleting job");

    }
    
    if (verbose)
      printf("sigchld_handler: exiting\n");

    return;
  }
}
  /* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
  void
    sigint_handler(int sig) 
  {
    pid_t pid;
    if (verbose)
      printf("sigint_handler: entering\n");
    
    if ((pid = jobs_fgpid()) > 0){
      /* send SIGINT signal to the job of PID=pid*/
      kill(pid,SIGINT);
    }
    
    if (verbose)
      printf("sigint_handler: exiting\n");
    
    return;
  }

  /*
   * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
   *     the user types ctrl-z at the keyboard. Catch it and suspend the
   *     foreground job by sending it a SIGTSTP.  
   */
  void
    sigtstp_handler(int sig) 
  {
    pid_t pid;
    if (verbose)
      printf("sigtstp_handler: entering\n");
    
    if ((pid = jobs_fgpid()) > 0){
      /* send SIGTSTP signal to the job of PID=pid*/
      kill(pid,SIGTSTP);
    }
    
    if (verbose)
      printf("sigtstp_handler: exiting\n");
    
    return;
  }
