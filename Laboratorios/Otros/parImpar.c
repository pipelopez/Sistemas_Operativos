/*
	Programa par o impar
*/

#include <stdio.h>

//variable global
int numero;
char terminar;

int main(){		
	while (terminar!='q'){
		printf("Ingrese un número: ");
		scanf("%d", &numero);
		if (numero%2==0){
			printf("El número %d es par\n", numero);

		}else{
			printf("El número %d es impar\n", numero);
		}		
		printf("¡Presione la tecla 'q' si desea terminar u otra para continuar!\n");
		setbuf(stdin, NULL);
		scanf("%c", &terminar);	
				}	
	return 0;
}
