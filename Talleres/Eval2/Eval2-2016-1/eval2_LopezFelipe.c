/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : eval2_LopezFelipe.c
 * Compilation  : gcc -Wall eval2_LopezFelipe.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>// printf, scanf, setbuf, fflush
#include <stdlib.h>//malloc
#include <string.h>

/* Definicion de macros y constantes. */
#define MAX_CHARACTER_NAME 50
#define MAX_CHARS_LINE 20

typedef struct {
    char especie[MAX_CHARACTER_NAME];
    char nombre[MAX_CHARACTER_NAME];
    char sexo[MAX_CHARACTER_NAME];
    int edad;
} mascota;

/* Declaracion de funciones. */
int getNumPets(FILE *f);
void getPetInfo(mascota *masc, FILE *f);
void printPetInfo(mascota *masc);
void separatePetsPerSpecie(mascota *masc, FILE *caninos, FILE *felinos);
void reproductiva (mascota *masc);

/* Variables globales. */
int numMascotasInFIle = 0;
int enlisted_mascotas =0;

/* Main function. */
int main(int argc, char *argv[]) {
    /* Variables locales. */
    int exitValue;
    char *fileEntrada;
    FILE *mascotasFile;
    char *fileSalidaCaninos;
    FILE *salidaCaninos;
    char *fileSalidaFelinos;
    FILE *salidaFelinos;
    mascota *mascotas;


    /* Obtener informacion. */
    // Validación: Número de argumentos traídos de consola.
    if (argc != 4) {
            printf("\nError: Numero de parametros invalido.\nDebe iniciar asi: ./1.out <entrada.csv> <salidaCaninos.txt> <salidaFelinos> \n");
        exit(0);
        }
    /* Hacer operaciones. */
    fileEntrada = argv[1];
    fileSalidaCaninos = argv[2];
    fileSalidaFelinos =argv[3];

    mascotasFile = fopen(fileEntrada, "r");
    if(mascotasFile == NULL) {
          printf("No se pudo abrir el archivo.\n");
          exit(0);
    }

  salidaCaninos = fopen(fileSalidaCaninos, "w+");
    if(salidaCaninos == NULL) {
            printf("No se pudo abrir el archivo.\n");
            exit(0);
    }

salidaFelinos = fopen(fileSalidaFelinos, "w+");
 if(salidaFelinos == NULL) {
              printf("No se pudo abrir el archivo.\n");
              exit(0);
          }

    numMascotasInFIle = getNumPets(mascotasFile);

          if (numMascotasInFIle <= 0) {
              printf("Error: No hay mascotas en el archivo\n");
              exit(0);
            }

          printf("Hay %d mascotas en el archivo de entrada\n", numMascotasInFIle);

          /* Obtener espacio dinámico en memoria. */
        mascotas = (mascota *)malloc(sizeof(mascota)* MAX_CHARS_LINE);

        //Realizar operaciones
        getPetInfo(mascotas, mascotasFile);
        printPetInfo(mascotas);
        separatePetsPerSpecie(mascotas, salidaCaninos, salidaFelinos);
        reproductiva (mascotas);

        //Cerrar archivos y liberar memoria
        exitValue = fclose(mascotasFile);
        if(exitValue == 0) {
            printf("se cerró el archivo mascotas.\n");
        }

        exitValue = fclose(salidaCaninos);
        if(exitValue == 0) {
            printf("se cerró el archivo salida caninos.\n");
        }

        exitValue = fclose(salidaFelinos);
        if(exitValue == 0) {
            printf("se cerró el archivo salida felinos.\n");
        }

        /* Free memory. */
        free(mascotas);
    /* Mostrar resultados. */

    return 0;
}

/* Implementacion de funciones. */
int getNumPets(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
}

void getPetInfo(mascota *masc, FILE *f) {
    /* Local variables. */
    int i = 0;
    char *token;
    char lines[MAX_CHARS_LINE];

    for (i = 0; i < numMascotasInFIle; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        while(token!=NULL) {
            strcpy((char *)masc->especie,token);
            token = strtok(NULL, ";");
            strcpy((char *)masc->nombre,token);
            token = strtok(NULL, ";");
            strcpy((char *)masc->sexo,token);
            token = strtok(NULL, ";");
            masc->edad = atoi(token);
            token = strtok(NULL, ";");
        }
        masc++;
        enlisted_mascotas++;
    }
    printf("Los usuarios del archivo de entrada fueron registrados exitosamente.\n");
}

void printPetInfo(mascota *masc){
    int i=0;
    if(enlisted_mascotas==0){
        printf("No se han ingresado datos aún.\n");
        return;
    }

    //Listar empleados
   printf("\n\tLista de mascotas\n");
   printf("%-15s%-15s%-15s%-15s\n", "Especie", "Nombre", "Sexo", "Edad");
   for(i=0; i<enlisted_mascotas; i++){
       printf("%-15s%-15s%-15s%-15d\n", masc->especie, masc->nombre, masc->sexo, masc->edad);
       masc++;
   }
}


void separatePetsPerSpecie(mascota *masc, FILE *caninos, FILE *felinos) {
    int i = 0;
    for (i = 0; i < enlisted_mascotas; i++) {
      char *option = masc->especie;
        switch (*option){
          case 'C':
          fprintf(caninos, "%-15s%-15s%-15s%-15d\n", masc->especie, masc->nombre, masc->sexo, masc->edad);
          printf("\nLos datos se almacenaron correctamente en el archivo caninos.\n");
          break;
          case 'F':
          fprintf(felinos, "%-15s%-15s%-15s%-15d\n", masc->especie, masc->nombre, masc->sexo, masc->edad);
          printf("Los datos se almacenaron correctamente en el archivo felinos.\n");
          break;
          }
          masc++;
    }
}

void reproductiva (mascota *masc){
  int i = 0;
  int menoresCat=0;
  int reproduceCat=0;
  int mayoresCat=0;
  int reproduceCan=0;
  int menoresCan=0;
  int mayoresCan=0;

  for (i = 0; i < enlisted_mascotas; i++) {
    char *option = masc->especie;
      switch (*option){
        case 'C':
        if(masc->edad>7 && masc->edad<204){
          reproduceCat++;
        }
        if(masc->edad<7){
          menoresCat++;
        }
        if(masc->edad<7){
          mayoresCat++;
        }
        break;
        case 'F':
        if(masc->edad>7 && masc->edad<204){
          reproduceCan++;
        }
        if(masc->edad<7){
          menoresCan++;
        }
        if(masc->edad<7){
          mayoresCan++;
        }
        break;
        }
        masc++;
  }

  printf("\nGatos\n");
  printf("Menores de 7 meses %d\n", menoresCat);
  printf("En etapa reproductiva %d\n", reproduceCat);
  printf("Mayores a 17 años %d\n", mayoresCat);
  printf("Perros\n");
  printf("Menores de 7 meses %d\n", menoresCan);
  printf("En etapa reproductiva %d\n", reproduceCan);
  printf("Mayores a 17 años %d\n", mayoresCan);

}
