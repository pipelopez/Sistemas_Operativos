#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_h1, pid_h2, pid_h3;
	int status_h1, status_h2, status_h3;
	pid_t pid_n;
	int status_n;

	int i = 0;

	pid_h1 = fork();

	if(pid_h1 == 0){ //Si es el hijo
		pid_n = fork();
		if(pid_n == 0){
			i++;
			printf("NIETO: i = %d\n",i);
		}else{
			wait(&status_n);
			i++;
			printf("HIJO 1: i = %d\n",i);
		}
	}else{
		pid_h2 = fork();
		if(pid_h2 == 0){
			i++;
			printf("HIJO 2 : i = %d\n",i);
		}else{
			pid_h3 = fork();
			if(pid_h3 == 0){
				i++;
				printf("HIJO 3 : i = %d\n",i);
			}else{
				wait(&status_h1);
				wait(&status_h2);
				wait(&status_h3);
				i++;
				printf("PAPÁ : i = %d\n",i);
			}
		}
	}
	return 0;
}