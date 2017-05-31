#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  int status;

  printf("PADRE: Mi PID es %d\n", getpid());
  printf("PADRE: El PID de mi padre es %d\n", getppid());
  pid = fork();

  if(pid == 0){
    sleep(5);
    printf("HIJO: Mi PID es %d\n", getpid());
    printf("HIJO: El PID de mi padre es %d\n", getppid());
    printf("HIJO: Fin!!\n");
  }else {
    printf("PADRE: Mi PID es %d\n", getpid());
    printf("PADRE: El PID de mi hijo es %d\n", pid);
    wait(&status);
    printf("PADRE: Mi hijo ha finalizado con estado %d\n",status);
    printf("PADRE: Fin!!\n");
  }
exit(0);
}
