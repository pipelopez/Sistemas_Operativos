//Fuente original: http://www.tldp.org/LDP/lpg/node11.html

#include <stdio.h>  //Libreria de entrada/salida
#include <unistd.h> //Librería para el manejo de procesos
#include <string.h> //Librería para bzero y strlen
#include <stdlib.h>  //Librería estandar, necesaria para usar exit()
#include <sys/types.h> //Definiciones de varios tipos de datos usados en llamadas al sistema
#include <sys/wait.h> //Necesario para usar wait()

int main(void)
{
        int     fd[2];  //Descriptor de archivo, del fd[0] es para recibir sd[1] es para enviar
        pid_t   childpid;  //id del proceso hijo
        char    mensaje[80];  //Mensaje a enviar
        char    readbuffer[80]; //Buffer de entrada

        if (pipe(fd) == -1) {//Creamos el pipe y retorna fd.
            fprintf(stderr,"Pipe failed");
            exit(1);
        }

        if((childpid = fork()) < 0){ //Se solicita duplicar el proceso, si retorna -1, es error.
                perror("fork");
                exit(1);
        }

        //Si es el proceso padre
        if(childpid != 0) {
                printf("padre: "); //Creamos una especie de prompt
                bzero(mensaje,80); //Inicializamos el buffer en 0
                fgets(mensaje,79,stdin); //Capturamos el mensaje del usuario
                write(fd[1], mensaje, (strlen(mensaje)+1)); //Enviamos el mensaje por el pipe
                wait(NULL); //Esperamos a que finalice el proceso hijo FIXME: machetazo.
                //Aquí el proceso hijo nos envía un mensaje
                read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Hijo dice: %s", readbuffer); //Mostramos el mensaje recibido del hijo
        }
        else{ //Si es el proceso hijo....
                read(fd[0], readbuffer, sizeof(readbuffer)); //Leemos lo que nos envía el padre
                printf("Padre dice: %s",readbuffer); //Mostramos el mensaje
                printf("hijo: "); // Creamos una especie de prompt para el hijo
                bzero(mensaje,80); //Inicializamos el buffer en 0
                fgets(mensaje,79,stdin); //Capturamos el mensaje del usuario
                write(fd[1], mensaje, (strlen(mensaje)+1)); //Se lo enviamos al padre
        }
        close(fd[0]);
        close(fd[1]);
        return(0); // Fin del proceso.
}
