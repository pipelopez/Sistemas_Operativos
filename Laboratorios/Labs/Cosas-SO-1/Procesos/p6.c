#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_h1, pid_h2, pid_n1, pid_n2, pid_n3, pid_n4;
	int status_h1, status_h2, status_n1, status_n2, status_n3, status_n4;
	printf("holiiiiii\n");
	printf("Padre: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
	
	pid_h1 = fork();//Hacemos 1 hijo
	if(pid_h1 == 0){ //Si es el hijo 1.
		printf("Hijo 1: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
		pid_n1 = fork(); //Hacemos nieto 1
		if(pid_n1 == 0){ //Si es el nieto 1
			printf("Nieto 1: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
			exit(1);
		}else{//Si es el hijo 1...
			wait(&status_n1); //Esperemos a que acabe el nieto 1
			printf("status_n1: %d\n", WEXITSTATUS(status_n1));
			pid_n2 = fork(); //Hacemos el nieto 2
			if(pid_n2 == 0){
				printf("Nieto 2: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
				exit(2);
			}
			wait(&status_n2); //Esperamos al nieto2
			printf("status_n2: %d\n", WEXITSTATUS(status_n2));
		}
		
		
		exit(3);
	}else{ //Si es el padre
		wait(&status_h1); //Esperamos que acabe el hijo 2
		printf("status_h1: %d\n", WEXITSTATUS(status_h1));
		pid_h2 = fork(); //Hacemos hijo 2
		if(pid_h2 == 0){ //Si es el hijo 2 
			printf("Hijo 2: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
			pid_n3 = fork(); //hacemos nieto 3
			if(pid_n3 == 0){ //Si es el nieto 3...
				printf("Nieto 3: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
				exit(4);
			}else{ //Si es el hijo 2
				wait(&status_n3); //Esperamos por el nieto 3
				printf("status_n3: %d\n", WEXITSTATUS(status_n3));
				pid_n4 = fork(); //Hacemos nieto 4
				if(pid_n4 == 0){
					printf("Nieto 4: PID: %d, PID padre directo: %d \n", getpid(), getppid() );
					exit(5);
				}
				wait(&status_n4);
				printf("status_n4: %d\n", WEXITSTATUS(status_n4));
			}

			exit(6);
		}else{
			wait(&status_h2);
			printf("status_h2: %d\n", WEXITSTATUS(status_h2));
			exit(0);
		}

	}



	return 0;
}