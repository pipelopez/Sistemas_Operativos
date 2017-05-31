/*
    Examen #1: Lab SO.
    fecha: 21 sept 2015
    Supermercado
    por: Christian David Delany Tamayo
*/


//Directivas del preprocesador
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 64


//Declaración de funciones

void printBill(int *positions, int *amounts, int billCount);
void menu();
void initialize();
void newBill();
int lookUpByCode(int code);
void error(char *men);
void checkItem();
void addItem();

//Variables globales.
char buf[MAXLENGTH];
char itemNames[100][MAXLENGTH];
int itemCodes[100];
int itemValues[100];
int itemCount;


int main()
{
    initialize();
    menu();
    return 0;
}

void initialize(){
    strcpy(itemNames[0], "Arículo #1");
    strcpy(itemNames[1], "Arículo #2");
    strcpy(itemNames[2], "Arículo #3");
    strcpy(itemNames[3], "Arículo #4");
    strcpy(itemNames[4], "Arículo #5");
    strcpy(itemNames[5], "Arículo #6");

    itemCodes[0] = 101;
    itemCodes[1] = 102;
    itemCodes[2] = 103;
    itemCodes[3] = 104;
    itemCodes[4] = 105;
    itemCodes[5] = 106;

    itemValues[0] = 300;
    itemValues[1] = 500;
    itemValues[2] = 250;
    itemValues[3] = 100;
    itemValues[4] = 900;
    itemValues[5] = 600;

    itemCount = 6;
}

void menu(){
    char *c;
    c = malloc(sizeof(char));
    do{
        printf("\tMenú Principal\n\n");
        printf("a.\tNueva factura\n");
        printf("b.\tConsultar artículo\n");
        printf("c.\tIngresar artículo\n");
        printf("q.\tSalir\n");
        printf("\nSeleccione una opción: ");

        *c = getchar();
        getchar(); //Este se consume el retorno de carro

        switch(*c){
        case 'a':
            newBill();
            break;
        case 'b':
            checkItem();
            break;
        case 'c':
            addItem();
            break;
        case 'q':
            break;
        default:
            printf("\nOpción Incorrecta");
        }
    }while(*c != 'q');
}

void checkItem(){
    int code;
    int art;
    printf("Ingrese el código a consultar: ");
    fgets(buf, MAXLENGTH, stdin);
    sscanf(buf, "%d", &code);
    if((art = lookUpByCode(code)) < 0) {
        error("El código ingresado es incorrecto");
        return;
    }
    printf("\nCódigo: %d, Nombre: %s, Valor: %d\n",code,itemNames[art],itemValues[art]);
    printf("Presione enter para continuar\n");
    getchar();
}

void newBill(){

    int billCount;
    int itemCode;
    int itemPos;
    int itemAmount;

    int *shCarPositions;
    int *shCarAmounts;

    if(itemCount < 1){
        error("Debe ingresar almenos un artículo al sistema para hacer una factura.");
        return;
    }

    printf("Ingrese el número de artículos a facturar: ");
    fgets(buf, MAXLENGTH, stdin);
    sscanf(buf, "%d", &billCount);
    if(billCount < 1){
        error("El número de artículos ingresado es incorrecto");
        return;
    }

     shCarPositions = malloc(sizeof(int)*billCount);
     shCarAmounts = malloc(sizeof(int)*billCount);

     if( shCarPositions == NULL || shCarAmounts == NULL ){
        error("No se pudo reservar memoria para la factura");
     }

    for(int i = 0; i < billCount; i++){
        itemPos = -1;
        do{
            printf("Ingrese el código del artículo #%d: ",(i+1));
            fgets(buf, MAXLENGTH, stdin);
            sscanf(buf, "%d", &itemCode);
            if((itemPos = lookUpByCode(itemCode)) < 0){
                error("Codigo invalido o inexistente");
            }
        }while(itemPos < 0);

        do{
            printf("Ingrese la cantidad de artículo #%d (%s): ",(i+1),itemNames[itemPos]);
            fgets(buf, MAXLENGTH, stdin);
            sscanf(buf, "%d", &itemAmount);
            if(itemAmount < 1){
                error("Cantidad inválida");
            }
        }while(itemAmount < 1);

        *(shCarPositions+i) = itemPos;
        *(shCarAmounts+i) = itemAmount;
    }

    printBill(shCarPositions,shCarAmounts,billCount);


    free(shCarPositions);
    free(shCarAmounts);
    //printf("billcount: %d\n",billCount);
}

void addItem(){
    if(itemCount >= 100){
        error("Se llegó al límite de artículos en el sistema.");
        return;
    }

    int code = -1;
    int valor = -1;
    char name[MAXLENGTH];


    printf("\nIngrese el código del nuevo artículo: ");
    fgets(buf, MAXLENGTH, stdin);
    sscanf(buf, "%d", &code);
    if(code < 1){
        error("El código debe ser un entero positivo (menor que (2^31)-1)");
        return;
    }
    if(lookUpByCode(code) >= 0){
        error("El artículo ya existe");
        return;
    }

    printf("Ingrese el  nombre del nuevo artículo: ");
    fgets(buf, MAXLENGTH, stdin);
    sscanf(buf, "%s", name);
    if(strcmp(name,"") == 0){
        error("El nombre no debe estar vacío");
        return;
    }
    printf("Ingrese el  valor del nuevo artículo: ");
    fgets(buf, MAXLENGTH, stdin);
    sscanf(buf, "%d", &valor);
    if(valor < 1){
        error("El valor debe ser un número entero positivo");
        return;
    }

    itemCodes[itemCount] = code;
    strcpy(itemNames[itemCount], name);
    itemValues[itemCount] = valor;

    itemCount++;

}

void printBill(int *positions, int *amounts, int billCount){
    int sum = 0;

    int mult = 0;
    printf("\t\tFactura de venta\n\tNombre de la empresa\n\n");
    printf("%-6s%-15.15s%-8s%-8s\n","Cant","Descripción","V.Unit","Total");
    for(int i = 0; i < billCount; i++){
        mult = itemValues[*(positions+1)]*((int)*(amounts+i));
        sum += mult;
        printf("%-6d%-15.15s%-8d%-8d\n",*(amounts+i),itemNames[*(positions+1)],itemValues[*(positions+1)],mult);
    }
    printf("%25s: %-8d\n", "Total",sum);
    printf("\nPresione enter para continuar");
    getchar();
}

int lookUpByCode(int code){
    for(int i = 0; i < itemCount; i++){
        if(itemCodes[i] == code)
            return i;
    }
    return -1;
}

void error(char *men){
    printf("Error: %s\n",men);
    printf("\nPresione enter para continuar\n");
    getchar();
}


//void checkItem(){
//}

