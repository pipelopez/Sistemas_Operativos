#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_HIJOS 4

int main(){

	pid_t pid_hijo;

	int resultado, num1=0, num2=0, i=0;
	int valor;

	printf("#1: ");
	setbuf(stdin, NULL);
	scanf("%d", &num1);
	printf("#2: ");
	setbuf(stdin, NULL);
	scanf("%d", &num2);

	for(i=0; i<NUM_HIJOS; i++){
		pid_hijo = fork();
		if (pid_hijo == -1) {
			/* Error */
			printf("No fue posible crear un hijo\n");
			return -1;
		}

		if (pid_hijo == 0) {
			switch (i) {
				case 0:
				resultado = num1+num2;
				break;

				case 1:
				resultado = num1-num2;
				break;

				case 2:
				resultado = num1*num2;
				break;

				case 3:
				resultado = num1/num2;
				break;
			}
			return resultado;
		}
	}

	while(wait(&valor)>0){ //Falta comparar los identificadores para saber cuál es cuál
		printf("El resultado es %d\n",WEXITSTATUS(valor) );
	}//El padre espera los hijos
	return 0;

}
