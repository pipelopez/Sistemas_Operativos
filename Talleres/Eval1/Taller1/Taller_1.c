/*
 * Name         : taller1.c
 * Author       : Juangui Restrepo
 * Description  : Taller 1. Lista de trabajadores de EMPRENDOR.
 * Inportance   : Poner en practica los temas vistos para el
 *                primer laboratorio (Introduccion a C).
 * Compilation  : gcc -Wall taller1.c -o taller1.out
 * Execution    : ./taller1.out
*/

/* Including headers or libraries. */
#include <stdio.h>      // printf, scanf, setbuf, fflush
#include <stdlib.h>     // malloc

/* Definition of macros and constants. */
#define MAX_CHARS_NAME 50

/* Declaration of functions (prototypes). */
void getOption(char *_option);
void registerEmployees(char (*_names)[MAX_CHARS_NAME], float *_wages);
void showList(char (*_names)[MAX_CHARS_NAME], float *_wages, float *_total);
void getTotal(float *_wages, float *_total);
int existEmployees();

/* Global variables. */
int max_employees = 0;
int enlisted_employees = 0;

/* Main function. */
int main(int argc, char *argv[]) {

    /* Local variables. */
    char option = 'x';
    char (*names)[MAX_CHARS_NAME];
    float *wages;
    float total = 0;

    // Validation: Number of arguments from console.
    if (argc != 2) {
        printf("Error: Numero de parametros invalido.\nDebe iniciar asi: ./taller.out <numero maximo de trabajadores>\n");
		exit(0);
    }

    // Get argument from console and convert it to a number
    max_employees = atoi(argv[1]);

    // Validation: Argument is a positive integer.
    if(max_employees <= 0){
        printf("Error: Parametro invalido.\nDebe iniciar asi: ./taller.out <numero maximo de trabajadores>\n");
        exit(0);
    }

    printf("La lista tendra una capacidad maxima de %d trabajadores.\n", max_employees);

    /* Get free space in memory. */
    names = (char (*)[MAX_CHARS_NAME]) malloc(sizeof(char[MAX_CHARS_NAME]) * max_employees);
    wages = (float *) malloc(sizeof(float) * max_employees);

    do {
        getOption(&option);
        switch (option) {
            case 'a':
                registerEmployees(names, wages);
                break;
            case 'b':
                getTotal(wages, &total);
                break;
            case 'q':
                showList(names, wages, &total);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("La opcion '%c' no es valida. Volviendo al menu.\n", option);
                break;
        }
    } while(option != 'q');

    /* Free memory. */
    free(names);
    free(wages);

    return 0;
}

/* Implementation of functions. */

/* Punto 1 (20%): Mostrar un menu con las opciones disponibles. */
void getOption(char *_option) {
  printf("\nMENU DE OPCIONES\n");
  printf("\ta) Registrar trabajadores.\n");
  printf("\tb) Obtener el pago total.\n");
  printf("\tq) Mostrar la lista y salir del programa.\n");
  printf("Seleccione una opcion: ");
  setbuf(stdin, NULL);
  scanf("\n%c", _option);
}

/* Punto 2 (40%): Registrar a los trabajadores. */
void registerEmployees(char (*_names)[MAX_CHARS_NAME], float *_wages) {
    /* Local variables. */
    int i = 0;
    int num_new_employees = 0;

    printf("Ingrese el numero de trabajadores a registrar: ");
    setbuf(stdin, NULL);
    scanf("%d", &num_new_employees);

    if (enlisted_employees + num_new_employees > max_employees) {
        printf("No es posible registrar %d trabajadores.\n", num_new_employees);
        printf("La capacidad maxima es %d y actualmente estan registrados %d.\n", max_employees, enlisted_employees);
        return;
    }

    for (i = enlisted_employees; i < enlisted_employees + num_new_employees; i++) {

        /* Get information of new employee. */
        printf("\nNombre del empleado #%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(_names+i));
        printf("Salario: ");
        setbuf(stdin, NULL);
        scanf("%f", _wages+i);
    }
    enlisted_employees += num_new_employees;
    printf("\nSe han registrado %d trabajadores en la lista.\n", num_new_employees);

}

/* Punto 3 (20%): Obtener el pago total. */
void getTotal(float *_wages, float *_total) {

    /* Local variables. */
    int i = 0;

    if (!existEmployees()) {
        printf("No se puede calcular el total porque no se han registrado trabajadores.\n");
        return;
    }
    *_total = 0;
    for (i = 0; i < enlisted_employees; i++) {
        *_total += *(_wages+i);
    }
    printf("\nEl pago total es de: %.2f$\n", *_total);
}

/* Punto 4 (20%): Mostrar la lista. */
void showList(char (*_names)[MAX_CHARS_NAME], float *_wages, float *_total) {

    /* Local variables. */
    int i = 0;

    if (!existEmployees()) {
        printf("No hay trabajadores para mostrar.\n");
        return;
    }

    printf("|%-12s|%-12s|\n", "Nombre", "Salario");
    for (i = 0; i < enlisted_employees; i++) {
        printf("|%-12s|%-12.2f|\n", *(_names+i), *(_wages+i));
    }
    printf("|%12s|%-12.2f|\n", "Total ", *_total);

}

int existEmployees() {
    if (enlisted_employees) {
        return 1;
    }
    return 0;
}
