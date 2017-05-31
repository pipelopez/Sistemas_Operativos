#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void factorialHijo(int numHijo,int valorFact);
long factorial(int valorFact);

int main(int argc, char const *argv[])
{
	pid_t pid_hijo1, pid_hijo2, pid_hijo3;
	int status1, status2, status3;
	int i;
	
	if((pid_hijo1 = fork()) == 0){
		for(i = 1; i <= 10; i++){
			factorialHijo(1,i);
		}
	}else if((pid_hijo2 = fork()) == 0){
		for(i = 1; i <= 10; i++){
			factorialHijo(2,i);
		}
	}else if((pid_hijo3 = fork())== 0){
		for(i = 1; i <= 10; i++){
			factorialHijo(3,i);
		}
	}else{
		wait(&status1);
		wait(&status2);
		wait(&status3);
	}

	return 0;
}

void factorialHijo(int numHijo,int valorFact){
	int fact = factorial(valorFact);
	printf("HIJO%d: fact(%d) = %d\n",numHijo,valorFact,fact);
	//fflush(stdout);
	return;
}

long factorial(int valorFact){
	//printf("%d\n",valorFact);
	if(valorFact <= 1){
		return 1;
	}else{
		return factorial(valorFact-1)*valorFact;
	}
}