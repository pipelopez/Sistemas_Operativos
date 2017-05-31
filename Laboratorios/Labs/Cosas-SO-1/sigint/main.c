
//Esta librería se usa para poder usar mecanísmos de entrada/salida básicos (printf, scanf)
#include<stdio.h>
//Contiene lo necesario para poder especificar como el programa maneja señales mientras se ejecuta
#include<signal.h>

//Declaramos el manejador de excepciones, explicado abajo.
void manejador(int signo);

//Función principal
int main(void){
    char c; //Caracter que validará la salida del programa
      /*

      Con la llamada signal le pedimos al SO que registre a la función manejador (segundo parámetro) en el kernel como
      el manejador de la señal SIGINT(primer parámetro) que es la señal llamada cuando se presiona control-c

      signal retorna SIG_ERR si la petición no puede ser cumplida. Algunas señales no pueden ser manejadas,
      (Por ejemplo SIGKILL o SIGSTOP).
      */
    if (signal(SIGINT, manejador) == SIG_ERR){
        printf("\nNo se puede capturar SIGINT\n");
        return -1;
    }

    //Invitamos al usuario a enviar un SIGINT
    printf("Este programa captura un SIGINT (interrupt)\n");
    printf("Para probarlo, presione control-C\n");
    do{//Hacemos esto para que el usuario tenga tiempo de enviar el signti

        printf("Presione enter para salir\n");
        c = getchar();
    }while(c != '\n');
    return 0;
}


/*
Definimos un manejador de señales

El manejador de excepciones es una función que contiene la lógica que se ejecutará
cuando se reciba determinada señal.

El parámetro de entrada es un entero que representa un tipo de señal.
Por ejemplo, en caso de presionarse Control-C, la señal sería SIGINT

Se dice que las funciones manejadoras idealmente deben ser ser 'reentrantes', esto quiere decir que
en caso de que por algún motivo se interrumpa la ejecución de la función manejadora,
el estado del programa (variables) debe quedar consistente, ya que de lo contrario
se podrían obtener resultados inesperados.

Si se presiona control-c(envía sigint) se ejecuta esta función.
*/
void manejador(int signo){
    //Si la señal que nos envían es SIGINT...
    if (signo == SIGINT)
        printf("Recibí un SIGINT, eso no será suficiente para matarme >:D\n");//Indicamos al usuario que nos la enviaron
    //pero no finalizamos la ejecución del proceso....
}
