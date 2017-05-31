#include <stdio.h>
#include <stdlib.h>

#define MENU "MENU\n"
#define opcion1 "1.\tEl área de un triangulo\n"
#define opcion2 "2.\tEl área de un trapecio.\n"
#define opcion3 "3.\tEl área de un rectángulo\n"
#define opcion4 "4.\tEl área de un circulo\n"
#define opcionSalir "5.\tSalir.\n"
#define mensajeMenu "\nSeleccione una opción: "
#define tamBuf 11

/*
const unsigned int BUF_SIZE = 1024;
char buf[BUF_SIZE];
fgets(buf, BUF_SIZE, stdin);
sscanf(buf, "%s %d %f", e.name, &e.age, &e.bs);
*/

void menu();
void areaTriangulo();
void areaTrapecio();

int main(void){
    menu();
}

void menu(){
    char *c;
    c = malloc(sizeof(char));
    do{
        printf("%s",MENU);
        printf("%s",opcion1);
        printf("%s",opcion2);
        printf("%s",opcion3);
        printf("%s",opcion4);
        printf("%s",opcionSalir);
        printf("%s",mensajeMenu);

        *c = getchar();
        getchar(); //Este se consume el retorno de carro

        switch(*c){
        case '1':
            areaTriangulo();
            break;
        case '2':
            areaTrapecio();
        }
    }while(*c != '5');

}

void areaTriangulo(){
    char base[tamBuf];
    char altura[tamBuf];
    int iBase, iAltura;
    printf("Ingrese base: ");
    fgets(base, tamBuf, stdin);
    printf("Ingrese altura: ");
    fgets(altura, tamBuf, stdin);
    iBase = atoi(base);
    iAltura = atoi(altura);
    printf("\nEl área del triangulo de base %d cm y altura %d cm es %d cm2\n\n",iBase,iAltura,(iBase*iAltura/2));
}

void areaTrapecio(){
    char baseMenor[tamBuf];
    char baseMayor[tamBuf];
    char altura[tamBuf];
    int iBaseMenor, iAltura, iBaseMayor;
    printf("Ingrese base menor: ");
    fgets(baseMenor, tamBuf, stdin);
    printf("Ingrese base mayor: ");
    fgets(baseMayor, tamBuf, stdin);
    printf("Ingrese altura: ");
    fgets(altura, tamBuf, stdin);
    iBaseMenor = atoi(baseMenor);
    iAltura = atoi(altura);
    iBaseMayor = atoi(baseMayor);
    printf("\nEl área del trapecio de bases %d cm, %d cm y altura %d cm es %d cm2\n\n",iBaseMenor,iBaseMayor,iAltura,(((iBaseMenor+iBaseMayor)*iAltura)/2));
}
