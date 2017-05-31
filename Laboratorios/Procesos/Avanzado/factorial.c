#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int factorial(int numero);

int main(){
  int status, pid_hijo1, pid_hijo2, pid_hijo3, i;

  pid_hijo1 = fork();
  if (pid_hijo1==0) {
    for (i = 0; i < 10; i++) {
      printf("Hijo 1: FACT(%d)=(%d)\n", i, factorial(i) );
    }
    exit(0);
  }

  pid_hijo2 = fork();
  if (pid_hijo2==0) {
    for (i = 0; i < 10; i++) {
      printf("Hijo 2: FACT(%d)=(%d)\n", i, factorial(i) );
    }
    exit(0);
  }

  pid_hijo3 = fork();
  if (pid_hijo3==0) {
    for (i = 0; i < 10; i++) {
      printf("Hijo 3: FACT(%d)=(%d)\n", i, factorial(i) );
    }
    exit(0);
  }

  wait(&status);
  wait(&status);
  wait(&status);
  exit(EXIT_SUCCESS);


  return(wait(&status));
}

int factorial(int numero){
  int factorial =1;
  for (int i = 1; i <= numero; i++) {
    factorial = factorial*i;
  }
  return factorial;
}
