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

void race(){
  int i,status;
  for (i = 1; i <= 10; i++) /* on crée les fils */
    switch(fork())
      {
      case -1:
	fprintf(stderr,"erreur création processus %d\n",i);
	exit(EXIT_FAILURE);
      case 0:
	for(i = 0; i < 100000000; i++);
	printf("Je suis le fils %d, je viens d'arriver à mi-parcours\n",getpid());
	for(i = 0; i < 100000000; i++);
	exit(EXIT_SUCCESS);
      default:;
      }
    
  for(i = 1; i <= 10; i++){
    pid_t pid_fils = wait(&status);
    if(WIFEXITED(status))
      printf("Le fils %d est arrivé en position %d !\n",(int) pid_fils,i);
    else 
      {
	perror("fils termine anormalement");
	exit(EXIT_FAILURE);
      }
  }
}



int main(){

  race();

  return 0;
}
