#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	pid_t pid_hijo;
	pid_hijo = getpid();
	printf("El ID del proceso es: %d\n", (int)pid_hijo );
	printf("El ID del proceso padre es: %d\n", (int)getppid() );
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hasta la vista baby, \n");
	kill(pid_hijo,SIGKILL);
	printf("Hasta la vista baby\n");
	printf("Hasta la vista baby\n");
	printf("Hasta la vista baby\n");
	return 0;
}