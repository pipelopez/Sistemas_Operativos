#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
int pid;
int numHijos = 5;
int numProceso;

for(numProceso = 0; numProceso < numHijos; numProceso++) {
pid = fork();

if (pid == -1) {
  printf("Hubo un error con la creación del hijo.\n" );
  } else if(pid == 0) {
  printf("Soy el hijo con PID: %d\n", getpid());
  }
}

if (pid == 0) {// Logica del hijo
  printf("Soy el hijo #%d\n", numProceso);
}else {
  printf("Soy un padre perezoso\n");
}
return 0;
}
