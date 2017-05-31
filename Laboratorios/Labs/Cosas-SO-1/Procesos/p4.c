#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	pid_t pid_hijo, pid_padre;
	printf("El pid del programa principal es: %d\n",(int) getpid() );
	switch(pid_hijo = fork()){
		case -1:
			printf("Error al crear el proceso\n");
			return -1;
		case 0:
			printf("Proceso hijo:\n");
			printf("PID del proceso: %d\n",(int)pid_hijo );
			printf("PID del proceso padre %d\n",(int)getppid() );
			exit(0);
			printf("Esta instrucción nunca se ejecutará en el proceso hijo\n");
			break;
		default:
			printf("Proceso padre:\n");
			printf("Proceso hijo con PID: %d creado.\n",(int)pid_hijo );
			printf("PID del hijo: %d\n",(int)pid_hijo );
			printf("PID del padre %d\n",(int)getppid() );
	}
	return 0;
}