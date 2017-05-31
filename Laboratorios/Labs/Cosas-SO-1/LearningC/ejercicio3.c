#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Macros
#define NUMCHARNAME 30

//Declaración de funciones
double promedioPonderado(double *n, int *c, int tam);
int numeroMaterias();
void leerDatos(char (*nombres)[], double *notas, int *creditos, int num);
void mostrarDatos(char (*nombres)[], double *notas, int *creditos, int num);


//Main
int main(void){
    int num = numeroMaterias(); //Pedimos el número de materias

    char (*nombres)[NUMCHARNAME]; //Arreglo de vectores que guarda los nombres de las materias
    double *notas; //Arreglo de double que guarda las notas
    int *creditos; //Arreglo de  enteros que guar los créditos
    nombres = malloc(sizeof(char)*NUMCHARNAME*num); //tamano del caracter * 30 de longitud c/u * num de materias
    notas = malloc(sizeof(double)*num); //tamaño de notas es num*tam(doble)
    creditos = malloc(sizeof(int)*num);

    leerDatos(nombres,notas,creditos,num); //Se le piden los datos al usuario

    mostrarDatos(nombres,notas,creditos,num); //Se muestra la info de las materias y el promedio
    free(nombres);
    free(creditos);
    free(notas);
    return 0;
}

void mostrarDatos(char (*nombres)[NUMCHARNAME], double *notas, int *creditos, int num){
    printf("\n\n%15s%15s%16s\n", "Nombre","Nota","créditos");
    for(int i = 0; i < num; i++){
        printf("%15s%15.2lf%15d\n",(char *)(nombres+i), *(notas+i), *(creditos+i));
    }
    double prom = promedioPonderado(notas,creditos,num);
    printf("%30.2lf\n",prom);
}

void leerDatos(char (*nombres)[NUMCHARNAME], double *notas, int *creditos, int num){
    for(int i = 0; i < num; i++){
        printf("Ingrese el nombre de la materia #%d: ",(i+1));
        //scanf("%s", (char *)(nombres+i));
        setbuf(stdin,NULL);
        fgets((char *)(nombres+i), NUMCHARNAME, stdin);
        printf("Ingrese la nota de la materia #%d: ",(i+1));
        scanf("%lf", (notas+i));
        printf("Ingrese el número de créditos de la materia #%d: ",(i+1));
        scanf("%d", (creditos+i));
    }
}


int numeroMaterias(){
    int num;
    printf("Ingrese el número de materias vistas: ");
    scanf("%d",&num);
    return num;
}

double promedioPonderado(double *n, int *c, int tam){
    int i = 0;
    double pond = 0;
    int sumCreds = 0;
    while(i < tam){
        pond += ((*n)*(*c));
        sumCreds += (*c);
        n++;
        c++;
        i++;
    }
    return (pond/sumCreds);
}
