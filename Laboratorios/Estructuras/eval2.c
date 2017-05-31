/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall evalX_ApellidoNombre.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>
/* Definicion de macros y constantes. */

/* Declaracion de funciones. */

/* Variables globales. */
srtuc student{
  char name[20];
  int id;
  float avg;
};

/* Main function. */
int main() {

    /* Variables locales. */
    struct student student1{"Juan", 123, 4.5};//Creación de variable tipo estudiante con inicialización
    struct student student2;
    struct student student5[];//arreglo
    struct student *ptrstudent = &student1;//puntero
    /* Obtener informacion. */

    /* Hacer operaciones. */
    student1.avg=5.0;
    printf("Nombre: %s\n", student1.name);
    *(ptrstudent.avg)=4.0;
    ptrstudent->avg=2.3;

    printf("Ingrese su nombre estudiante 2 %c\n", &student2.name);//almacenar
    printf("Ingrese su nombre estudiante 2 %c\n", &student2.name[2]);//almacenar en segunda pos
    printf("Ingrese su nombre id 2 %d\n", &student2.id);
    strcpy(student2.name, "Jose");//Copiar cadena de caracteres
    strncpy();//Copia dando la cantidad máxima

    /* Mostrar resultados. */

    return 0;
}

/* Implementacion de funciones. */
