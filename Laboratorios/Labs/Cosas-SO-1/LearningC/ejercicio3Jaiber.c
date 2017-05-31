/*
    Taller #1: Lab SO.
    fecha: 14 sept 2015
    Mares en c
    por: Jaiber
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIGN 20
#define NUMCHARNAME 30

int main(void){
    int numSign = 0;
    char name[MAXSIGN][NUMCHARNAME];
    float grades[MAXSIGN];
    int i = 0;
    puts("Ingrese el número de materias:");
    scanf("%d",&numSign);
    printf("Numero materias: %d\n", numSign);

    for( i = 0; i< numSign; i++){
        puts("Ingrese el nombre de la materia: ");
        //scanf("%s", name);
        setbuf(stdin,NULL);
        fgets((char *)&name[i], NUMCHARNAME, stdin);
        printf("Ingrese la nota de la materia: ");
        scanf("%f",&grades[i]);
    }
    for( i = 0; i< numSign; i++){
        printf("Nombre: %s", name[i]);
        printf("Nota: %f\n", grades[i]);
    }
    return 0;

}
