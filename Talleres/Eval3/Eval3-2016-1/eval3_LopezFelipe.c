/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall evalX_ApellidoNombre.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>// printf, scanf, setbuf, fflush
#include <stdlib.h>//malloc
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/* Definicion de macros y constantes. */
#define MAX_CHARS_LINE 20

typedef struct {
    int real;
    int imaginario;
} complejo;

/* Declaracion de funciones. */
int getNumComplejos(FILE *f);
void getComplejos(complejo *comp, FILE *f);
void suma(complejo *comp);
void resta(complejo *comp);
void conjuga(complejo *comp);

/* Variables globales. */
int numComplejosInFIle = 0;

/* Main function. */
int main(int argc, char *argv[]) {

    /* Variables locales. */
    int exitValue;
    char *fileEntrada;
    FILE *file;
    complejo *complejos;
    pid_t padre, pid_hijo1, pid_hijo2, pid_hijo3;
    int status;


    /* Obtener informacion. */
    // Validación: Número de argumentos traídos de consola.
    if (argc != 2) {
            printf("\nError: Numero de parametros inválido.\nDebe iniciar asi: ./1.out <archivo.csv>\n");
        exit(0);
        }

    /* Hacer operaciones. */
    fileEntrada = argv[1];

    file = fopen(fileEntrada, "r");
    if(file == NULL) {
          printf("No se pudo abrir el archivo.\n");
          exit(0);
    }

    numComplejosInFIle = getNumComplejos(file);

          if (numComplejosInFIle <= 0) {
              printf("Error: No hay números en el archivo\n");
              exit(0);
            }

          printf("Hay %d números en el archivo de entrada\n", numComplejosInFIle);

    complejos = (complejo *)malloc(sizeof(int)* MAX_CHARS_LINE);



    //Realizar operaciones
    getComplejos(complejos, file);

//Crear procesos para llamar las operaciones


    padre = fork();
    if(padre == 0) {
      printf("Soy el padre con PID: %d\n", getpid());
      pid_hijo1 = fork();
      if (pid_hijo1==0) {
        printf("Soy un proceso hijo con PID: %d SUMAR\n", getpid());
        suma(complejos);
        exit(0);
      }else{
        wait(&status);
      }

      pid_hijo2 = fork();
      if (pid_hijo2==0) {
        printf("Soy un proceso con pid: %d RESTAR\n",getpid());
        resta(complejos);
        exit(0);
      }else{
        wait(&status);
      }

      //espera el nieto1
      pid_hijo3 = fork();
      if (pid_hijo3 ==0) {
        printf("Soy un proceso con pid: %d CONJUGA\n",getpid());
       conjuga(complejos);
        exit(0);
      }else{
        wait(&status);
        exitValue = fclose(file);
        if(exitValue == 0) {
            printf("se cerró el archivo de complejos.\n");
        }
        /* Free memory. */
        free(complejos);
      }
    exit(EXIT_SUCCESS);
  }

    /* Mostrar resultados. */

    return(wait(&status));
}

/* Implementacion de funciones. */
int getNumComplejos(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num;
}

void getComplejos(complejo *comp, FILE *f) {
    //Local variables.
    int i = 0;
    char *token;
    char lines[MAX_CHARS_LINE];

    for (i = 0; i < numComplejosInFIle; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        while(token!=NULL) {
          comp->real = atoi(token);
          token = strtok(NULL, ";");
          comp->imaginario = atoi(token);
          token = strtok(NULL, ";");
        }
        comp++;
    }
    printf("Los números del archivo de entrada fueron registrados exitosamente.\n");
}

void suma(complejo *comp){
  int i;
  int sumaReal=0, sumaImaginario=0;
  for(i=0; i<numComplejosInFIle; (i+=2)){
    sumaReal= (comp->real)+((comp+1)->real);
    sumaImaginario = (comp->imaginario)+((comp+1)->imaginario);
    printf("Resultado= %d,%d\n",sumaReal, sumaImaginario );
    comp++;
    comp++;
  }
}

void resta(complejo *comp){
  int i;
  int sumaReal=0, sumaImaginario=0;
  for(i=0; i<numComplejosInFIle; (i+=2)){
    sumaReal= (comp->real)-((comp+1)->real);
    sumaImaginario = (comp->imaginario)-((comp+1)->imaginario);
    printf("Resultado= %d,%d\n",sumaReal, sumaImaginario );
    comp++;
    comp++;
  }
}


void conjuga(complejo *comp){
  int i;
  int sumaReal=0, sumaImaginario=0;
  for(i=0; i<numComplejosInFIle; i++){
    sumaReal= (comp->real);
    sumaImaginario = ((-1)*(comp->imaginario));
    printf("Resultado= %d,%d\n",sumaReal, sumaImaginario );
    comp++;
  }
}
