// Fuente original: http://www.cs.cf.ac.uk/Dave/C/node27.html

#include <sys/types.h> //Definiciones de varios tipos de datos usados en llamadas al sistema
#include <sys/ipc.h> //Se usa para comunicación entre procesos
#include <sys/shm.h> //Librería que contiene lo necesario para usar memoria compartida
#include <unistd.h> //Constantes y tipos variados
#include <string.h> //para fgets
#include <stdlib.h> // Librería estandar
#include <stdio.h> //IO básica
#include <sys/wait.h> //Necesario para usar wait()

void error(char *msg);


int main(void){
    pid_t childpid; // Id del proceso hijo
    int shmid; //Guardaremos aquí el id del segmento de memoria compartida
    key_t key; //Nombre del espacio de memoria compartida
    char *shm; //Apuntador al primer segmento de memoria compartida
    char buffer[51]; //Buffer para el mensaje.
    struct shmid_ds *salida = NULL; //guaramos la estructura que retorna shmctl

    key = 5679; //Nombre del segmento de memoria que se compartirá


    if((childpid = fork()) == -1){ //Se solicita duplicar el proceso, si retorna -1, es error.
                error("no se pudo hacer fork");
    }

    if(childpid != 0){ //Proceso padre

        /*
            shmget() es una llamada que retorna el id de un segmento de memoria compartida
            asociado a un segmento de memoria de almenos SHMSZ bytes. shmget recibe como parámetro:

            1. Una clave que funciona como el "nombre" del área compartida
            2. La cantidad de bytes mínima que se necesita
            3. Una bandera que especifica la manera en la que el segmento será usado (permisos)

            En este caso nos interesa crear el espacio, por eso agregamos la bandera IPC_CREAT

            shmget retorna el identificador del segmento de memoria compartida en System V
        */
        if ((shmid = shmget(key,  10*sizeof(char), IPC_CREAT | 0666)) < 0) {
            error("shmget solicitud de espacio rechazada padre");
        }

        /*
          Ahora adjuntamos el segmento a nuestro espacio de memoria
          shmat() hace una petición para adjuntar un segmento de memoria compartida al espacio del proceso que está corriendo
          shmat retorna la dirección inicial del segmento de memoria compartida

          shmat recibe como parámetro el identificador de memoria compartida, una dirección que puede indicar
          que dirección se debe retornar (si es null se retorna la posicion inicial del segmento) y una
          bandera que puede indicar ciertas opciones.
         */
        if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) { //Si él elemento que hay en la posición inicial es un -1...
            error("shmat no pudo adjuntar segmento de memoria");
        }

        /*
         Ahora vamos a poner algo en memoria para que lo lea el otro proceso
         */

        bzero(buffer,50); //Inicializa en ceros el buffer
        printf("Escriba un mensaje para el hijo: ");
        fgets(buffer,255,stdin); //Obtenemos la entrada del usuario
        strcpy(shm, buffer);

        /*
            Ahora esperamos que el hijo nos indique que leyó los datos
            la señal que hemos demarcado con dicho propósito es un asterisco

         */
        while (*shm != '*') // Leemos el espacio compartido con el hijo
           sleep(1); //Esperamos...

        wait(NULL);

        //Ahora solicitamos al sistema eliminar el segmento de memoria compartida
        if (shmctl(shmid, IPC_RMID, salida) == -1) {
            perror("shmctl: falló la eliminación del segmento de memoria compartida");
            exit(1);
        }
    }else{ //Si somos el proceso hijo....
        //OJO SI PASAN 7 SEGUNDOS Y NO SE MANDA NADA PUEDE FALLAR.
        sleep(7); //Esperamos 7 segundos a que nos manden el mensaje

        //Abrimos el espacio de memoria compartida que solicitó el padre
        //En el código del padre está mejor descrito.
        if ((shmid = shmget(key, 10*sizeof(char), 0666)) < 0) { //Si no se ha creado o pasa algo malo....
            error("shmget solicitud rechazada hijo");
        }

        /*
            Análogamente al código del padre, adjuntamos el segmento de memoria
            compartida a nuestro espacio de memoria.
        */
        if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
            error("shmget solicitud rechazada hijo");
        }

        //Ahora, suponemos que el padre ya escribió algo en el tiempo pasado
        //Y lo leemos desde el espacio de memoria al que apunta SHM.
        printf("padre dice: %s",shm);

        /*
            Por último, le decimos al padre que leimos el mensaje que nos envió
            y que puede finalizar la ejecución.
        */
        *shm = '*';
    }

    exit(0);
}

void error(char *msg){
    perror(msg); //Imprime un mensaje de error al stderr
    exit(0); //Salimos
}
