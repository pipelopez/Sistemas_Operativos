/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall evalX_ApellidoNombre.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>
#include <stdlib.h>//malloc

/* Definicion de macros y constantes. */
#define MAX_CHARS_NAME 50

/* Declaracion de funciones. */
void getOption(char *_option);
void registerEmployees(char (*names)[MAX_CHAR_NAME], float *wages);

/* Variables globales. */
int max_employees =0;
int enlisted_employees =0;


/* Main function. */
int main(int argc, char *argv[]) {
    
    /* Variables locales. */	
	char option ='x';
	char(*names)[MAX_CHARS_NAME];
	float *wages;
	
	
	/*Validar argumentos*/   
 	if(srgc !=2){
		printf("Número de argumentos no es válido\n");
		exit(0);
	}

	max_employees = atoi(argv[1]); //convierte lo que se le entrega en un número pero si detecta que son letras devuelve un cero

	if(num_maximo <=0 ){
		printf("Argumento no es válido \n");
	}

	

	printf("El número máximo de trabajadores a registrar es %d\n", max_employees );
	
	/* Obtener informacion. */
    
    /* Hacer operaciones. */

	names = (char (*)[MAX_CHARS_NAME]) malloc(sizeof(char*[MAX_CHARS_NAME])*max_employees);
	wages = (float *) malloc(sizeof(float)*max_employees);
	
	do{    
		getOption (&option);
		switch(option){
			case 'a':
				registerEmployees(names, wages);
			break;
			case 'b':
				//getTotal	
			break;
			case 'q':
				//showList
			break;
			default:
				printf();
		}
    /* Mostrar resultados. */
    
    return 0;
}

/* Implementacion de funciones. */

void getOption(char *_option){
	printf("\nMENU DE OPCIONES\N");
	printf("\Ta) Registrar trabajadores.\n" );
	printf("\Tb) Obtener el pago total.\n" );
	printf("\Tc) Mostrar la lista y salir del programa.\n" );
	printf("\Ta) Registrar trabajadores.\n" );
	setbuf(stdin, NULL);
	scanf("\n%c", _option);
}

void registerEmployees(char (*names)[MAX_CHAR_NAME], float *wage){
	
	int num_new_employees, i;

	printf("Número de usuarios a registrar \n");
	setbuf(stdin, NULL);
	scanf("%d\n", &num_new_employees);
		
	if(enlisted_employees + num_new_employees > max_employees){
		printf("No es posibles registrar %d trabajadores \n", num_new_employees );
		printf("La capacidad máxima es %d y hay registrado %d\n", max_employees,(enlisted_employees + num_new_employees) );
	return
	}

	for(i=0; i<num_new_employees, i++){	
		printf("Nombre: \n");
		setbuf(stdin, NULL);
		scanf("%s\n", (char *)names+i);

		printf("Salario: \n");	
		setbuf(stdin, NULL);
		scanf("%f\n", wages+i);
}
}
