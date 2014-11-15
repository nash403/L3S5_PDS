/* 
Nom :
Honoré NINTUNZE
Valentin PIERART
*/


#ifndef FORKFORK_H
#define FORKFORK_H

/*définition du forkfork qui fait exécuter une fonction par un petit fils*/

typedef void (*func_t) (void *);
void forkfork(func_t f, void *arg);

#endif /*FORKFORK_H*/
