#include <stdio.h>
#include <stdlib.h>

//#define SIZE 3

void getData(float data[], int size);
void getDataPtr(float *data, int size);
void printData(float data[], int size);
void printDataPtr(float *data, int size);
float average(float *data,int size);
float min(float *data,int size);
float max(float *data,int size);
int main(int argc, char *argv[]){
    
int size;
//float numbers[SIZE];            //Static
float *numbers;
float promedio,minimo,maximo;
size = atoi(argv[1]);
numbers = malloc(sizeof(float)*size);        

printf("%d", size);

getDataPtr(numbers, size);    
printDataPtr(numbers, size);
promedio=average(numbers,size);
minimo=min(numbers,size);
maximo=max(numbers,size);
printf("El mayor es: %.1f\n",maximo);
printf("El menor es: %.1f\n",minimo);
printf("El promedio es: %.1f\n",promedio);
free(numbers);
return 0;

}
float min(float *data,int size){
    int i;
    float m=*data;
    float aux;
    for(i=1;i<size;i++){
        aux=*(data+i);
        if(aux<m){
            m=aux;
        }
    }
    
    return m;
}

float max(float *data,int size){
    int i;
    float m=*data;
    float aux;
    for(i=1;i<size;i++){
        aux=*(data+i);
        if(aux>m){
            m=aux;
        }
    }
    return m;
}

float average(float *data,int size){
    int i;
    float aveg=0;
    if(size==0){
        printf("La longitud es cero, posible división por cero");
        return 0;    
    }
    for(i=0;i<size;i++){
        aveg+=*(data+i);
    }
    aveg=aveg/size;

    return aveg;
}

void getData(float data[], int size){
    
    int i;
    printf("ingrese %d datos\n", size);
    for(i=0; i<size; i++){
        scanf("%f", &data[i]);
    }

}

void getDataPtr(float *data, int size){
    
    int i;
    printf("\ningrese %d datos\n", size);
    for(i=0; i<size; i++){
        scanf("%f", data+i);
    }
}


void printData(float data[], int size){

    int i;
    printf("Los datos son: \n");
    for(i=0; i<size; i++){
        printf("%.1f\n", data[i]);
    }
}

void printDataPtr(float *data, int size){

    int i;
    printf("Los datos son: \n");
    for(i=0; i<size; i++){
        printf("%.1f\n", *(data+i));
    }
}
