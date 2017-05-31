//Esta librería se usa para poder usar mecanísmos de entrada/salida básicos (printf, scanf)
#include <stdio.h>
//Contiene lo necesario para poder especificar como el programa maneja señales mientras se ejecuta
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void manejador(int signo);

//Función principal
int main(void){
  //Catch sigint
  signal(SIGINT, manejador);
  sleep(3);
  printf("No SIGINT within 3 seconds.\n");

  //Ignore sigint
  signal(SIGINT, SIG_IGN);
  printf("Ignoring SIGINT\n");
  sleep(3);
  printf("No SIGINT within 3 seconds\n");

  //Default action for SIGINT

  signal(SIGINT, SIG_DFL);
  printf("Default action for SIGINT.\n");
  sleep(3);
  printf("No SIGINT within 3 seconds\n");

}

void manejador(int signo){
    //Si la señal que nos envían es SIGINT...
    printf("Recibí un SIGINT, número, %d\n",signo);//Indicamos al usuario que nos la enviaron
    exit(0);
}