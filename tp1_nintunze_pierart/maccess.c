/*Noms :
  NINTUNZE Honoré
  PIERART Valentin
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "fatal.h"
int main (int argc, char* argv[]){ /*./maccess [nom_fichier] [options: -w,-r ou -x] [option -v] */
  int i;
  char* msg;
  msg = "./maccess : illegal option.\n\tUsage: ./maccess [nom_fichier] [options: -rwx] [option: -v]\n";
  if ((argc < 2) || (argc > 6)) {
    printf("%s",msg); 
    return 0;
  }
  
  for(i = 2; i < argc; i++){
    fatal(argv[i][0] != '-', msg, 101);
    switch (argv[i][1]) 
      {
      case 'r' : access(argv[1],R_OK); break;
      case 'w' : access(argv[1],W_OK); break;
      case 'x' : access(argv[1],X_OK); break;
      }
  }
  
  if ((argv[argc-1][0] == '-') && (argv[argc-1][1] == 'v'))
    /* switch (errno) */
    /*   { */
    /*   case EACCES : printf("L'accès serait refusé au fichier lui‐même, ou il n'est pas permis de parcourir l'un des répertoires du préfixe du chemin de pathname\n"); break; */
    /*   case ELOOP : printf("Trop de liens symboliques ont été rencontrés en parcourant pathname.\n"); break; */
    /*   case ENAMETOOLONG : printf("pathname est trop long.\n"); break; */
    /*   case ENOENT : printf("Un composant du chemin d'accès pathname n'existe pas ou est un lien symbolique pointant nulle part.\n"); break; */
    /*   case ENOTDIR : printf("Un élément du chemin d'accès pathname n'est pas un répertoire.\n"); break; */
    /*   case EROFS : printf("On demande une écriture sur un système de fichiers en lecture seule.\n"); break; */
    /*   default : printf("Autre erreur\n"); */
    /*   } */
    printf("Error : %s",strerror(errno));
  
    
  return errno; 
}
