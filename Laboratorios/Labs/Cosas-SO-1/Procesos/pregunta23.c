#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char const *argv[]){
	pid_t pid;
	int status;
	printf("PADRE: Mi PID es: %d\n",getpid());
	printf("PADRE: El PID de mi padre es: %d\n",getppid());
	if((pid = fork())==0){
		sleep(5);
		printf("HIJO: Mi PID es: %d\n",getpid());
		printf("HIJO: El PID de mi padre es: %d\n",getppid());
		printf("HIJO: fin!");
	}else{
		printf("PADRE: Mi PID es: %d\n",getpid());
		printf("PADRE: El PID de mi hijo es: %d\n",pid);
		wait(&status);
		printf("PADRE: fMi hijo ha finalizado con status: %d!\n",status);
		printf("PADRE: fin!");
	}

	exit(0);
}