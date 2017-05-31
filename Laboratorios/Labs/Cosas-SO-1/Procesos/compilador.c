#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_h1;
	int status;
	if (argc != 3){
		fprintf(stderr,"uso: %s <entrada.c> <salida>\n",argv[0]);
		fprintf(stderr, "ejemplo:\n%s programa.c a.out\n",argv[0] );
		exit(-1);
	}
	pid_h1 = fork();
	if(pid_h1 == 0){
		//Proceso que ejecuta ls
		execl("/usr/bin/gcc", "/usr/bin/gcc", "-Wall", "-o", argv[2] , argv[1],  NULL);
	}else{
		wait(&status); //Esperamos por un proceso para que no se quede huerfanito
		if(!WEXITSTATUS(status)){
			printf("Compilación completada exitosamente\n");
		}else{
			printf("ERROR EN COMPILACIÓN.\n");
		}
	}
	return 0;
}