#include <stdio.h>

int main(void)
{
    char nombre[20] = "inicial";
    char salir = 'n';
    float nota;
    while(salir != 'q'){
        printf("Digite el nombre y nota del estudiante\n");
        scanf(" %s %f",nombre, &nota);
        printf("%-.5s\n",nombre);
        printf("%.1f\n",nota);
        printf("Presione 'q' para salir, otra tecla para continuar: ");
        scanf(" %c",&salir);

    }
}
