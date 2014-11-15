/*Noms :
  NINTUNZE Honoré
  PIERART Valentin
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main (int argc, char* argv[]) {
  int opt;  

  if ((argc < 2) || (argc > 6)) { 
    printf("./maccess : illegal option.\n\tUsage: ./maccess [nom_fichier] [options: -rwx] [option: -v]\n"); 
    return 0;
  }

  while ((opt = getopt(argc, argv,"rwxv")) != -1) {
    switch(opt){
    case 'r': if (access(argv[1],R_OK) == 0) printf("OK en lecture\n"); else printf("NON en lecture\n"); break;
    case 'w': if (access(argv[1],W_OK) == 0) printf("OK en ecriture\n"); else printf("NON en ecriture\n");break;
    case 'x': if (access(argv[1],X_OK) == 0) printf("OK en execution\n"); else printf("NON en execution\n");break;
    case 'v': printf("Error : %s\n",strerror(errno));
    default: exit(500);
    }
  }

  return 0;

}
