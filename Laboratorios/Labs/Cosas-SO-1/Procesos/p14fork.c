#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int fd;
	pid_t pid;
	int i;
	if((pid = fork()) < 0){
		perror("fork falló");
		exit(-1);
	}else if(pid == 0){
		for (i = 0; i < 20; ++i)
		{
			printf("hijo: %d\n", i );
			sleep(1);
		}
	} else{
		for (i = 0; i < 20; i +=3)
		{
			printf("padre: %d\n",i );
			sleep(1);
		}
	}
	return 0;
}