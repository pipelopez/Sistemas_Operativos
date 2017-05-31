#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
int pid;
int numHijos = 5;
int numProceso;

for(numProceso = 0; numProceso < numHijos; numProceso++) { //wexitstatus
  pid = fork();

  if (pid == -1) {
    printf("Error\n" );
      exit(0);
  } else if(pid == 0) {//HIJO

  }
}

if (pid == 0) {
  // Logica del hijo
  printf("Soy el hijo #%d\n", numProceso);

}
// Imprimir algun mensaje de error
else {
printf("Soy un padre perezoso\n");
}

while(wait(NULL)>0);//El padre espera los hijos
return 0;

}
