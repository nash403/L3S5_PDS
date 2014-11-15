/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "fatal.h"
#define MAXLINE 255


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
	fatal(i >= MAXLINE,"Ligne trop longue\n",1) ;
      if(c == '\n')
	break ;
      line[i] = c ;
      i++ ;
    }
  line[i] = '\0' ;
  return i ;
}

/*compte le nombre de ligne d'un fichier*/
int wl(FILE* file)
{
  int cpt,i;
  char line[MAXLINE];
  cpt = 0;
  i = readl(file, line);
  while (i != EOF)
    {
      cpt++;
      i = readl(file,line);
    }
  return cpt ;
}

/*affiche les n dernière lignes*/
void tail(FILE* file,char buffer[],int n) {
  int nb_line,cpt;
  cpt = 0;
  nb_line = wl(file);
  
  rewind(file);

  while (cpt < (nb_line - n)) {
    cpt++;
    readl(file,buffer);
  }

  while ((cpt = readl(file,buffer)) != EOF)
    printf("%s\n",buffer);
  
  return ;
}


int main(int argc, char* argv[]) {
  char line[MAXLINE],*p;
  FILE* file;
  long nb;
  int num;
  
  
  fatal(argc > 3, "Illegal argument : \nUsage : \n\t\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);

  file = fopen(argv[1],"r");

  fatal(file == NULL, "Impossible d'ouvrir le fichier\n",EXIT_FAILURE);

  if (argc == 2)
    tail(file, line,10);
  else {
    nb = strtol(argv[argc-1],&p,0);

    if (errno != 0 || *p != '\0' || nb > INT_MAX)
      fatal(1==1,"Erreur : argument non entier\nUsage : \n\t\t./tail [nom fichier] [nombre de lignes à afficher (optionnel)]\n",EXIT_FAILURE);
    else
      num = nb;
    tail(file,line,num);
  }

  fclose(file);

  return 0;
}
