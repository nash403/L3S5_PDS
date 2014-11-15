/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include "fatal.h"
#define MAXLINE 255
#define MAXSIZE 4096


/* affiche la fin du fichier file à partir de la position current_pos*/
void tail(FILE* file,off_t index) {
  int fd, nb_lignes_lues;
  char buffer[MAXSIZE];
  fd = fileno(file);
  lseek(fd,index+1,SEEK_SET);
  while ((nb_lignes_lues = read(fd,buffer,MAXSIZE)) > 0)
    write(1,buffer,nb_lignes_lues);

  return;
}

/* retrouve l'index du premier caractère à écrire puis ecrit la fin du fichier à partir de cet index*/
void index_tail_buffer(FILE* file, long int nb_lignes) {
  off_t current_pos,i,end;
  char c;
  int compteur_ligne, longueur_ligne,status;

  /* on lit le fichier à partir de la fin pour retrouver le début des nbLignes */
  status = fseek(file,0,SEEK_END);
  fatal(status == -1,"Erreur lseek\n",EXIT_FAILURE);
  current_pos = ftell(file);
  i = current_pos;
  end = current_pos;
  for ( longueur_ligne = 0,compteur_ligne =0; i >=0; i--){
    c = fgetc(file);
    if (c == '\n' && (end - i) > 1) { /* si on a un '\n' à la fin */
      compteur_ligne++; 
    }
    if (compteur_ligne == nb_lignes) break;
    longueur_ligne++;
    fatal(longueur_ligne > MAXLINE,"Ligne trop longue\n",EXIT_FAILURE);
    current_pos--;
    status = fseek(file,current_pos,SEEK_SET);
    fatal(status == -1,"Erreur lseek\n",EXIT_FAILURE);
  }
  
  tail(file,current_pos);
  return ;
}




int main(int argc, char* argv[]) {
  FILE* file;  
  long int argument/*,index*/;
  char *p;

  fatal(argc > 3, "Illegal argument : \nUsage : \n\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);

  file = fopen(argv[1],"r");

  fatal(file == NULL, "Impossible d'ouvrir le fichier\n",EXIT_FAILURE);

  if (argc == 2){
    index_tail_buffer(file, 10);
  } else {
    argument = strtol(argv[argc-1],&p,0); /*on récupère le nombre de ligne à afficher*/

    if (*p != '\0')
      fatal(*p != '\0',
	    "Erreur : argument non entier\nUsage : \n\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);
    else{
      index_tail_buffer(file,argument);
    }  
  }

  fclose(file);

  return 0;
}
