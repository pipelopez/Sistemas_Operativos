#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void imprimir(int *p, int tam);
void llenar(int *p, int tam);
int promedio(int *p, int tam);

int main(int argc, char **argv){
    srand(time(NULL));
    int n = atoi(*(argv+1));
    int *arr;
    arr = malloc(sizeof(int)*n);
    llenar(arr, n);
    //imprimir(arr,n);
    int prom = promedio(arr,n);

    printf("Promedio: %d\n",prom);
}


void llenar(int *p, int tam){
    int i = 0;
    while(i < tam){
        *p = rand()%50;
        p++;
        i++;
    }
}

int promedio(int *p, int tam){
    int i = 0;
    int sum = 0;
    while(i < tam){
        sum += *p;
        p++;
        i++;
    }
    return (sum/tam);
}

void imprimir(int *p, int tam){
    int i = 0;
    while(i < tam){
        printf("Pos %d: %d\n",i,*p);
        p++;
        i++;
    }
}
