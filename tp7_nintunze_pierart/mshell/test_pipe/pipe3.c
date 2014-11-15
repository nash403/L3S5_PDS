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
	int status;
	
	status = pipe(fds);
	assert(status != -1);
	
	switch(fork()) /* cat process */
	{
		case -1 : assert(0);
		case 0 :
			close(fds[STI]);
			status = dup2(fds[STO],STO);
			assert(status != -1);
			execlp("cat", "cat", "Makefile", (char *) 0);
			exit(EXIT_FAILURE);
		default: ;
	}
	
	/*status = pipe(fds);
	assert(status != -1);*/
	status = dup2(fds[STI],STI);
	assert(status != -1);
	switch(fork()) /* egrep process */
	{
		case 1 : assert(0);
		case 0 :
			status = dup2(fds[STI],STI);
			assert(status != -1);
			status = dup2(fds[STO],STO);
			assert(status != -1);
			execlp("egrep", "egrep", "all", (char *) 0);
			exit(EXIT_FAILURE);
		default : ;
	}
	
	switch(fork()) /* wc process */
	{
		case 1 : assert(0);
		case 0 :
			close(fds[STO]);
			status = dup2(fds[STI],STI);
			assert(status != -1);
			execlp("wc", "wc","-l", (char *) 0);
			exit(EXIT_FAILURE);
		default : ;
	}
	
	close(fds[STI]);
	close(fds[STO]);
	wait(NULL);
	wait(NULL);
	
	exit(EXIT_SUCCESS);
}
