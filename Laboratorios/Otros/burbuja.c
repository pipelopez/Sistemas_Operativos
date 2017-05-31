/*Método burbuja*/

#include <stdio.h>

void printDataPtr(int *lista, int size);
void ordenarBurbujaPtr(int *lista, int size);
void pedirInfo(int *lista, int size);

int tam=0, i=0;

int main(){
	int lista[tam]; //arreglo que contiene los numeros	

//solicito el ingreso de tamaño
	printf("Por favor ingrese la cantidad de datos a ordenar: ");	   
	scanf("%d",&tam);
	printf("El tamaño ingresado es: %d\n", tam);

//Solicito los valores a ingresar en el arreglo
    pedirInfo(lista, tam);
/*for (i=0; i<tam; i++) { 
		printf("Dame el dato %d: ",i+1); 
		scanf("%d\n", &lista[i]); //preguntar por qué no funciona
		printf("La posición actual de i es: %d\n", (lista+i));
		} */

//Muestro la lista de datos en la forma que se ingresaron
	printf("La lista desordenada es:");
	for(i=0; i<tam; i++){
		printf("%d ", *(lista+i));
	}
	i=0;

    ordenarBurbujaPtr(lista, tam);

//Ordeno los datos haciendo uso de burbuja
/*	for(i=1; i<tam; i++){
			for(j=0; j<tam-1; j++){
				if(lista[j]>lista[j+1]){
					temp=lista[j];
					lista[j]=lista[j+1];
					lista[j+1]=temp;	
				}
			}
	}*/
	
//Muestro los datos ordenados
	printf("\nLa lista ordenada es:");
	printDataPtr(lista, tam);
	printf("\n");
	
return 0;
}

//Métodos usando punteros
void printDataPtr(int *lista, int size){    
    for(i=0; i<size; i++){
		printf("%d ", *(lista+i));
	}
	i=0;
}

void ordenarBurbujaPtr(int *lista, int size){
    int j,temp=0;
    for(i=1; i<size; i++){
			for(j=0; j<size-1; j++){
				if(*(lista+j)>*(lista+(j+1))){
					temp=*(lista+j);
					*(lista+j)=*(lista+(j+1)); //* significa dato, lo de los paréntesis es la posición
					*(lista+(j+1))=temp;	
				}
			}
	}
	i=0;
}

void pedirInfo(int *lista, int size){    
    for (i=0; i<size; i++) { 
		printf("Dame el dato %d: ",i+1); 
		scanf("%d\n", lista+i);	//Si quiero llevar un dato a una posición le quito el
		//printf("La posición actual de i es: %d\n", (lista+i));
		} 
	i=0;
}
