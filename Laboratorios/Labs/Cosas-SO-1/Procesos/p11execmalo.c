#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_h1, pid_h2;
	int status;
	pid_h1 = fork();
	if(pid_h1 == 0){
		//Proceso que ejecuta ls
		execl("/bin/lsdf", "/bin/lsdf", "-l", "/", NULL);
	}else{
		pid_h2 = fork();
		if(pid_h2 == 0){
			execl("/bin/date", "/bin/date", NULL);
		}else{
			wait(&status); //Esperamos por un proceso
			wait(&status); //Esperamos el otro
			printf("Hasta la vista baby\n");
		}
	}
	return 0;
}