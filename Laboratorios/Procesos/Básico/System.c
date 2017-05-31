#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

int valor_retornado;

printf("ID del proceso: %d\n", (int)getpid());

printf("ID del proceso padre: %d\n", (int)getppid());

valor_retornado = system("cal");

valor_retornado = system("ls -l");

printf("Velor retornado: %d\n", valor_retornado);
return valor_retornado;

}
