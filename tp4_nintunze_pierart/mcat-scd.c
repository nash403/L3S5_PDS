/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "fatal.h" 

void cat(char* name) {
  int fd,status;
  char * buffer = (char *) malloc(MCAT_BUFSIZ*sizeof(char));

  fd = open(name,O_RDONLY);

  while ((status = read(fd,buffer,MCAT_BUFSIZ)) > 0) {
    write(1,buffer,status);
  }
  close(fd);

  return;
  
}


int main(int argc, char* argv[]) {
  int i;
  fatal(argc < 2, "Argument manquant.\nUsage :\n\t./mcat-scd [nom fichier]...",EXIT_FAILURE);

  for (i = 1; i < argc; i++)
    cat(argv[i]);

  return 0;
}
