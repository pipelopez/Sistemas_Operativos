#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("Hola");
	fflush(stdout);
	fork();
	printf("Mundo");
	fflush(stdout);
	fork();
	printf("!\n");
	return 0;
}