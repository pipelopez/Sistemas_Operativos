#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid_hijo, pid_nieto;
	printf("Hola");
	fflush(stdout);
	pid_hijo = fork();
	if(pid_hijo == 0){
		printf(" mundo");
		fflush(stdout);
		pid_nieto = fork();
		if(pid_nieto == 0){
			printf("!\n");
		}
	}
	return 0;
}