/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall evalX_ApellidoNombre.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/* Definicion de macros y constantes. */
#define MAX_CHARS_LINE 200
#define MAX_NUMBERS_IN_LINE 50

/* Declaracion de funciones. */
int getNumLineas(FILE *f);
int numbersInFile(FILE *f);
void registerNumbers(FILE *f);

/* Variables globales. */
int numLineas = 0;
int numerosArray[12];

/* Definition of structures. */
typedef struct {
    int number;
} numero;

void *perfecto(void *param){
  numero num1= *((numero *)param);
  int *result = (int *)malloc(sizeof(int));
  int i;
  int suma =0;

  for(i=1;i<num1.number;i++)
  {
      if(num1.number%i==0) //La condición es que el numero dividido entre num1 de como resto 0
      {
          suma= suma+i;
      }
  }
  if(suma == num1.number){
    *result = suma;
  }else{
    *result=0;
  }
  pthread_exit((void *)result);
}

/* Main function. */
int main(int argc, char *argv[]) {
  int exitValue, cantidadNumeros, i;
  char *fileEntrada;
  FILE *numerosFile;
  numero numeros[12];
  pthread_t id[12];
  int *results[12];

    /* Variables locales. */

    /* Obtener informacion. */
    if (argc != 2) {
            printf("\nError: Numero de parametros invalido.\nDebe iniciar asi: ./1.out <entrada.csv> \n");
    		exit(0);
        }
    fileEntrada = argv[1];
    numerosFile = fopen(fileEntrada, "r");
    if(numerosFile == NULL) {
          printf("No se pudo abrir el archivo\n");
          exit(0);
      }

    /* Hacer operaciones. */
    numLineas = getNumLineas(numerosFile);
    cantidadNumeros = numbersInFile(numerosFile);

    //int num[numLineas];
    /* Obtener espacio dinámico en memoria. */
    //numeros = (numero *)malloc(sizeof(numero) * MAX_NUMBERS_IN_LINE);
    registerNumbers(numerosFile);

    for(i=0;i<12;i++){ //para los create
      numeros[i].number = numerosArray[i];
      pthread_create(&id[i], NULL, perfecto, (void *)&numeros[i]);
    }

    for(i=0;i<12;i++){ //para los join
      pthread_join(id[i], (void **)&results[i]);
      printf("Resultado: %d\n", *results[i]);
    }

    /* Mostrar resultados. */
    exitValue = fclose(numerosFile);
    if(exitValue == 0) {
        printf("se cerró el archivo números.\n");
    }

    return 0;
}

/* Implementacion de funciones. */
int getNumLineas(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
}

int numbersInFile(FILE *f) {
    /* Local variables. */
    int i = 0;
    int cant = 0;
    char *token;
    char lines[MAX_CHARS_LINE];

    for (i = 1; i < numLineas; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        while(token!=NULL){
          cant++;
          token = strtok(NULL, ";");

        }

    }
    return cant;
}

void registerNumbers(FILE *f) {
    /* Local variables. */
    int i=0, j=0;
    char *token;
    char lines[MAX_CHARS_LINE];

    for (i = 1; i < numLineas; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
          while(token!=NULL){
            numerosArray[j]=atoi(token);
            token = strtok(NULL, ";");
            j++;
        }
    }
    printf("Los usuarios del archivo de entrada fueron registrados exitosamente.\n");
}
