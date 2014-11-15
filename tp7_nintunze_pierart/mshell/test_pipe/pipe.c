#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STO 1
#define STI 0

int main(int argc, char* argv[]){
	int fds[2];
	int status,ito;
	
	assert(argc > 1);

	assert(!strcmp(argv[0],"./pipe"));

	for (ito = 2; ito < argc ; ito++)
		if(!strcmp(argv[ito],"to"))
			break;
			
	assert(ito < argc - 1); /* check that ito isn't the last token */
	
	argv[ito] = NULL;
	
	assert((status = pipe(fds)) != -1);
	
	switch(fork()) /* command1 process */
	{
		case -1 : assert(0);
		case 0 :
			close(fds[STI]);
			status = dup2(STO,fds[STO]);
			assert(status != -1);
			execvp(argv[1],argv);
			exit(EXIT_FAILURE);
		default: ;
	}
	
	switch(fork()) /* command2 process */
	{
		case 1 : assert(0);
		case 0 :
			close(fds[STO]);
			status = dup2(STI,fds[STI]);
			assert(status != -1);
			execvp(argv[ito+1],argv+ito+1);
			exit(EXIT_FAILURE);
		default : ;
	}
	
	close(fds[STI]);
	close(fds[STO]);
	wait(NULL);
	wait(NULL);
	
	exit(EXIT_SUCCESS);
}
