#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
	int valor_retornado;
	printf("El id del proceso es: %d\n",(int)getpid());
	printf("El id del padre del proceso es: %d\n",(int)getppid());
	valor_retornado = system("cal");
	valor_retornado = system("ls -l");
	return valor_retornado;
}