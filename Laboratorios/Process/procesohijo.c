#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  pid_t pid_hijo;

  printf("Ejemplo fork. Este proceso va a crear otro proceso\n\n");
  printf("El pid del programa principal es: %d\n", (int)getpid());
  switch (pid_hijo=fork()) {
    case-1:/*Código ejecutado en caso de error*/
    printf("Error al crear el proceso\n");
    return -1;
    case 0: /*Código ejecutado por el hijo*/
    printf("PROCESO HIJO:\n");
    printf("PID del hijo:%d\n", (int)pid_hijo);
    break;
    default:/*Codigo ejecutado por el padre*/
    printf("PROCESO PADRE: Proceso hijo con PID %d creado\n", (int)pid_hijo );
  }
  /*Esta linea será ejecutada por ambos procesos(padre e hijo)*/
  printf("Fin del proceso cuyo hijo tiene un PID de %d\n", (int)pid_hijo);
}
