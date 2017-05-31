#include <stdio.h>

char nombres[3][10] = { "fulano", "mengano", "perano"};

int main(void){
    char i;
    char *a;
    char (*b)[10];

    a = (char *)nombres;

    printf("el nombre es %s\n", a);

    b = (char (*)[10])nombres[0];
    for(i = 0; i < 3;i++){
        printf("el nombre [%d] es %s\n",i,(char *)(b+i));
    }
}
