#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	pid_t pid_h1, pid_h2, pid_h3;
	pid_t pid_n;

	int i = 0;

	pid_h1 = fork();

	if(pid_h1 == 0){ //Si es el hijo
		pid_n = fork();
		if(pid_n == 0){
			i++;
			printf("NIETO: i = %d\n",i);
		}else{
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
				i++;
				printf("PAPÁ : i = %d\n",i);
			}
		}
	}
	return 0;
}