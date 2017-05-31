/*
	Programa nombres
*/

#include <stdio.h>

//variable global
char nombre[50];
float nota;
char terminar;

int main(){		
	while (terminar!='q'){
		printf("Ingrese su nombre: ");
		scanf("%s", nombre);
		printf("Ingrese su nota: ");
		scanf("%f", &nota);
		printf("Nombre Nota\n%-8.5s%-4.2f\n", nombre, nota);
		printf("¡Presione la tecla q si desea terminar u otra para continuar!");
		setbuf(stdin, NULL);
		scanf("%c", &terminar);			
	}	
	return 0;
}
