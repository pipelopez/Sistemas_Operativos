#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  pid_t pid_hijo, pid_nieto;
  //int status;

    printf("Hola ");
    fflush(stdout);//limpia el buffer e imprime en pantalla
    pid_hijo = fork();
    if(pid_hijo == 0) {
      printf("mundo");
      fflush(stdout);//limpia el buffer e imprime en pantalla
      pid_nieto = fork();
      if (pid_nieto==0) {
        printf("!\n");
        exit(0);
      }
    }
return 0;
}
