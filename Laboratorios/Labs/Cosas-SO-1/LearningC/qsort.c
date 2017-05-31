#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void llenar(int *p, int tam);
void seleccion(int *p, int size);
void swap(int *a, int *b);
void imprimir(int *p, int tam);

int main(void)
{
     srand(time(NULL));
     int arr[100];
     llenar(arr,100);
     imprimir(arr,100);
     seleccion(arr,100);
     imprimir(arr,100);
}

void seleccion(int *p, int size){
    int i = 0;
    int j;
    int min;
    while(i < size-1){
        j = i+1;
        min = i;
        while(j < size){
            if(*(p+j) < *(p+min)){
                min = j;
            }
            j++;
        }
        swap(p+i,p+min);
        i++;
    }
}

void imprimir(int *p, int tam){
    int i = 0;
    while(i < tam){
        printf("Pos %d: %d\n",i,*p);
        p++;
        i++;
    }
}

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a=*b;
    *b=temp;
}
void llenar(int *p, int tam){
    int i = 0;
    while(i < tam){
        *p = rand()%20;
        p++;
        i++;
    }
}


