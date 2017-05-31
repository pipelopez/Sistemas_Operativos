#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    pid_t pid_padre, pid_hijo1, pid_hijo2, pid_nieto1, pid_nieto2;
    int status;

    pid_padre = fork();
    if(pid_padre == 0) {
      printf("Soy el padre con PID: %d \n", getpid());
      pid_hijo1= fork();
      if (pid_hijo1==0) {
          printf("Soy el hijo1 con pid: %d y mi padre es: %d\n",getpid(), getppid() );
          exit(0);
      }
      printf("Esperando hijo1\n" );
      wait(&status);//espera el hijo1
      printf("Terminó el hijo1, creando hijo2...\n" );
      pid_hijo2= fork();//crea el hijo2
      if (pid_hijo2==0) {
        printf("Soy el hijo2 con pid: %d y mi padre es: %d\n",getpid(), getppid() );
        pid_nieto1 = fork();
        if (pid_nieto1==0) {
          printf("Soy el nieto1 con pid: %d y mi padre es: %d\n",getpid(), getppid() );
          exit(0);
        }
        printf("Esperando nieto1\n");
        wait(&status);//espera el nieto1
        printf("Terminó nieto1, creando nieto2...\n" );
        pid_nieto2 = fork();
        if (pid_nieto2==0) {
          printf("Soy el nieto2 con pid: %d y mi padre es: %d\n",getpid(), getppid() );
          exit(0);
        }
        printf("Esperando el nieto2\n" );
        wait(&status);//espera el nieto2
        printf("Terminó el nieto2, terminando hijo2...\n");
        exit(0);
      }
      printf("Esperando el hijo2\n" );
      wait(&status);//espera que termine el hijo2
      printf("Terminó el hijo2, saliendo...\n" );
      exit(EXIT_SUCCESS);
      }
return(wait(&status));
}
