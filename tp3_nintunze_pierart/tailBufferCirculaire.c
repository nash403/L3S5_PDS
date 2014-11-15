/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "fatal.h"
#define MAXLINE 255

struct line {
  char phrase[MAXLINE];
  struct line* next;
};

typedef struct line* buffer;

/*lit une ligne de fichier*/
int readl (FILE* file, char line[])
{
  int i;
  char c;
  i = 0 ;
  while (1)
    {
      c = fgetc(file) ;
      if (c == EOF)
	{
	  line[i] = '\0';
	  return EOF ;
	}
	fatal(i >= MAXLINE,"Ligne trop longue\n",EXIT_FAILURE) ;
      if(c == '\n')
	break ;
      line[i] = c ;
      i++ ;
    }
  line[i] = '\0' ;
  return i ;
}

/*affiche les n dernière lignes*/
void tail(FILE* file,int n) {
  int i,j,status;
  char buffer_line[MAXLINE];
  buffer tmp, buf = (buffer) malloc(n*sizeof(struct line));

  for(i = 0; i < n; i++) {  /*on lit n lignes et on rempli les structures*/
    tmp = (buffer) malloc(sizeof(struct line));
    
    if ((status = readl(file,buffer_line)) != EOF){
      strncpy(tmp->phrase,buffer_line,MAXLINE);
      tmp->next = &buf[i+1];
      buf[i] = *tmp;
    } 
    else {  /* s'il y a moins de n lignes on ecrit le buffer */
      for (j = 0;j < i; j++) {
	tmp = buf;
	printf("%s\n",buf->phrase);
	buf = buf->next;
	free(tmp);
      }
      return;
    }
  }

  /* on lit le reste du fichier jusqu'à la fin*/
  while ((status = readl(file,buffer_line)) != EOF) {  
    tmp = (buffer) malloc(sizeof(struct line)); /*créer case et l'initialiser*/
    strncpy(tmp->phrase,buffer_line,MAXLINE);
    tmp->next = buf;      /* lier nouvelle case à la première*/
    buf[n-1].next = tmp; /* lier dernière case à la nouvelle*/
    
    /* avancer buffer et libérer mémoire*/
    tmp = buf;            
    buf = buf->next;
    free(tmp);
  }
  
  /* une fois à la fin écrire buffer et libérer mémoire */
  for (i = 0; i < n; i++) {
    tmp = buf;
    printf("%s\n",buf->phrase);
    buf = buf->next;
    free(tmp);
  }
  return;
}


int main(int argc, char* argv[]) {
  char* p;
  FILE* file;
  int argument;
  fatal(argc > 3, "Illegal argument : \nUsage :\n\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);

  file = fopen(argv[1],"r");

  fatal(file == NULL, "Impossible d'ouvrir le fichier\n",EXIT_FAILURE);

  if (argc == 2)
    tail(file,10);
  else {
    argument = strtol(argv[argc-1],&p,0); /*on récupère le nombre de ligne à afficher*/

    fatal(*p != '\0',"Erreur : argument non entier\nUsage :\n\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);
    tail(file, argument);
  }

  fclose(file);

  return 0;
}
