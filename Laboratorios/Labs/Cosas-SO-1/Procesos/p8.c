#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	/*Creación del proceso hijo*/
	pid_t child_pid;

	child_pid = fork();
	if(child_pid > 0){
		/*proceso padre, duerme por 20s*/
		sleep(20);
	}else{
		exit(0);
	}
	return 0;
}