/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : eval1_LopezFelipe.c
 * Compilation  : gcc -Wall eval1_LopezFelipe.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>// printf, scanf, setbuf, fflush
#include <stdlib.h>//malloc

/* Definicion de macros y constantes. */
#define MAX_CHARACTER_NAME 50

/* Declaración de funciones. */
void getOption(char *_option);
void registerEmployees(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra);
void getSalaryEmploye(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra, float *_salario_extra, float *_totales, float *_total);
void showList(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra);

/* Variables globales. */
int max_employees = 0;
float extra_value = 0;
int enlisted_employees =0;

/* Main function. */
int main(int argc, char *argv[]) {

    /* Variables locales. */
    char option = 'x';
    char (*nombres)[MAX_CHARACTER_NAME];//arreglo de caracteres de tamaño 50 x posición
    float *salarios;//arreglo de salarios
    int *horas_extra;
    float *totales = 0;//total de salarios
    float *salario_extra=0;
    float total =0;

    /* Obtener informacion. */

    /* Hacer operaciones. */

    // Validación: Número de argumentos traídos de consola.
    if (argc != 3) {
            printf("\nError: Numero de parametros invalido.\nDebe iniciar asi: ./1.out <numero maximo de trabajadores> <valor hora extra>\n");
    		exit(0);
        }

        // Obtengo el argumento y lo convierto a número
        max_employees = atoi(argv[1]);//convierte lo que recibe a número
        setbuf(stdin, NULL); //limpiar el bufer

        extra_value = atof(argv[2]);
        setbuf(stdin, NULL); //limpiar el bufer

        /* Obtener espacio dinámico en memoria. */
        nombres = (char (*)[MAX_CHARACTER_NAME]) malloc(sizeof(char[MAX_CHARACTER_NAME]) * max_employees);
        salarios = (float *) malloc(sizeof(float) * max_employees);
        horas_extra = (int *) malloc(sizeof(int) * max_employees);
        totales = (float *) malloc(sizeof(float) * max_employees);
        salario_extra = (float *) malloc(sizeof(float) * max_employees);

        //Validar que el número ingresado sea positivo
    if(max_employees<=0){
        printf("\nError: El número de empleados ingresado no es válido,\ndebe ser un número mayor a cero.\n");
        exit(0);
    }else{
        printf("La lista tendrá una cantidad máxima de %d trabajadores\n", max_employees);
        do{
        getOption(&option);
        printf("\nLa opción escogida fue %c\n", option);
        switch (option){
            case 'a':
            registerEmployees(nombres, salarios, horas_extra);
            break;
            case 'b':
            showList(nombres, salarios, horas_extra);
            break;
            case 'c':
            getSalaryEmploye(nombres, salarios, horas_extra, salario_extra, totales, &total);
            break;
            case 'q':
            printf("\nSaliendo del programa..\n\n");
            break;
            default:
            printf("La opción %c escogida no es válida, seleccione de nuevo.\n", option);
        }
    }while(option !='q');
    }

    /* Liberar memoria. */
    free(nombres);
    free(salarios);
    free(horas_extra);
    free(totales);
    free(salario_extra);

    /* Mostrar resultados. */

    return 0;
}

/* Implementacion de funciones. */

//Punto 1 (20%) Función Menú
void getOption(char *_option){
    printf("\nMENÚ DE OPCIONES\n");
    printf("\ta) Registrar trabajadores.\n");
    printf("\tb) Ver lista de trabajadores.\n");
    printf("\tc) Calcular nómina.\n");
    printf("\tq) Salir del programa.\n");
    printf("Seleccione una opción: ");
    setbuf(stdin, NULL); //limpiar el bufer
    scanf("\n%c", _option);
}

//Punto 2 (20%) Registrar empleados
void registerEmployees(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra){
    int i;
    int num_new_employees=0;
    printf("\nIngrese el número de empleados a registrar: ");
    setbuf(stdin, NULL);

    // Obtengo el argumento y lo convierto a número
    scanf("%d", &num_new_employees);
    if(num_new_employees<=0){
        printf("\nEl valor ingresado no es válido, \ndebe ser un número entero mayor a cero.\n");
        return;
    }

    printf("El valor ingresado fue: %d\n", num_new_employees);

    //Verificar que los existentes + los nuevos < maximo permitido
    if(num_new_employees + enlisted_employees > max_employees){
        printf("No es posible registrar %d trabajadores.\n", num_new_employees);
        printf("La capacidad máxima es %d y actualmente están registrados %d.\n", max_employees, enlisted_employees);
        return;
    }

    //Enlistar empleados
    for(i=enlisted_employees; i<enlisted_employees+num_new_employees; i++){
        /* Obtener información del empleado. */
        printf("\nNombre del empleado N°%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(_nombres+i));
        printf("Salario: ");//Verifica que el salario sea un número
        setbuf(stdin, NULL);
        scanf("%f", _salarios+i);
        while(*(_salarios+i)<=0){
            *(_salarios+i) = 0;
            printf("\nEl valor ingresado no es válido, el salario debe ser mayor a cero.\nIngrese de nuevo el salario:");
            setbuf(stdin, NULL);
            scanf("%f", _salarios+i);
        }
        printf("Horas extra: ");//Verifica que el salario sea un número
        setbuf(stdin, NULL);
        scanf("%d", _horas_extra+i);
        while(*(_horas_extra+i)<0){
            *(_salarios+i) = 0;
            printf("\nEl valor ingresado no es válido debe ser un número igual o mayor a cero.\nIngrese de nuevo las horas extra: ");
            setbuf(stdin, NULL);
            scanf("%f", _salarios+i);
        }

    }

    //Actualizar valores e informar al usuario
    enlisted_employees += num_new_employees;
    printf("\nSe han registrado %d empleados en la lista.\n", num_new_employees);
    printf("El número total de empleados en la lista es %d.\n", enlisted_employees);
}

//Punt0 3 (20) mostrar la lista
void showList(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra){
    int i=0;
    if(enlisted_employees==0){
        printf("No se han ingresado datos aún.\n");
        return;
    }

    //Listar empleados
   printf("\n\tLista de trabajadores\n");
   printf("%-15s%-15s%-15s\n", "Nombre", "Salario base", "Horas extra");
   for(i=0; i<enlisted_employees; i++){
       printf("%-15s%-15.2f%-15d\n", *(_nombres+i), *(_salarios+i), *(_horas_extra+i));
   }
}


//Punto 4 (40%) Calcular salarios
void getSalaryEmploye(char (*_nombres)[MAX_CHARACTER_NAME], float *_salarios, int *_horas_extra, float *_salario_extra, float *_totales, float *_total){
    int i;
    //Verificar que hayan datos
    if(enlisted_employees==0){
        printf("Aún no se ha ingresado ningún salario\n");
        return;
    }

    *_total=0;
    for(i=0; i<enlisted_employees; i++){
      *(_salario_extra+i) = *(_horas_extra+i) * extra_value;//salario extra de cada uno
      *(_totales+i)= *(_salarios+i) + *(_salario_extra+i);//total de cada uno
        *_total += *(_totales+i); //total de todos
    }

    //Listar empleados
   printf("\n\t\tLista de trabajadores\n");
   printf("%-30s%-30s\n","Nombre de la empresa: XXX S:A", "Nit: 80808080");
   printf("%-15s%-15s%-15s%-15s\n", "Nombre", "Salario base", "Salario extra", "Total");
   for(i=0; i<enlisted_employees; i++){
       printf("%-15s%-15.2f%-15.2f%-15.2f\n", *(_nombres+i), *(_salarios+i), *(_salario_extra+i), *(_totales+i));
   }

   //Listar el total
   printf("%-45s%-15.2f\n", "Total", *_total);
}
