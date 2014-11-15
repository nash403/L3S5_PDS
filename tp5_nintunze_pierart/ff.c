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

void f(int* n,char* name){
  sleep(*n);
  fprintf(stdout,"Je la fonction %s lancée par forkfork et maintenant je suis le fils de %d\n",name,getppid());
}

static void f1(void *arg) { f(arg,"f1");}


int main (){
  int time = 4;

  forkfork(f1,&time);

  return 0;
 
}
