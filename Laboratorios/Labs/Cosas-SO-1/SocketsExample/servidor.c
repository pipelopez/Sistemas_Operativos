// Fuente original: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html


#include <stdio.h> //IO básica
#include <sys/types.h> //Definiciones de varios tipos de datos usados en llamadas al sistema
#include <sys/socket.h> // Lo necesario para usar sockets
#include <netinet/in.h> // Contiene lo necesario para conexiones por internet
#include <stdlib.h> // Librería estandar
#include <string.h> //para strlen y bzero
#include <unistd.h> //Constantes y tipos variados, necesaria para usar read y write

void error(char *msg);

int main(void){

     int sockfd;  //Aquí se guarda el descriptor de archivo del socket
     int newsockfd; //Aqui se guarda el descriptor de archivo del Socket asociado al cliente.
     int portno = 50000; //Aquí se guarda el puerto en host byte order (luego se transforma a network byte order)
     unsigned int clilen; //Tamaño de cli_addr
     char buffer[256]; //Buffer donde guardaremos los mensajes de entrada y salida
     struct sockaddr_in serv_addr; //Guardará la información relacionada a la dirección en internet del servidor
     struct sockaddr_in cli_addr; // Guardará la información del cliente que se conecte
     int n; // Guardará el número de caracteres leidos o escritos

     /*
        Creamos un nuevo socket
        sockfd contiene un descriptor de archivo (numero positivo) o bien un numero negativo en caso de error
        socket acepta 3 parámetros:
        1. Dominio al que pertenecen las direcciones (AF = Familia de direcciones), algunosposibles valores:
            -AF_INET: IPv4
            -AF_INET6: IPv6
            -AF_UNIX: Unix (Entre procesos locales)
            -AF_BLUETOOTH: Bluetooth
        2. Tipo del socket (semánticas), algunos posibles valores:
            -SOCK_STREAM: Confiable y secuencial (Orientado a la conexion)
            -SOCK_DGRAM: Datagramas (No confiable, con un tamaño máximo definido)
            -SOCK_RDM: Datagramas confiables que no garantizan el orden
        3. Protocolo, normalmente se deja en 0, el sistema selecciona la mejor opción (Comunmente TCP o UDP)
     */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) //Si el socket no se pudo crear....
        error("ERROR al abrir el socket");
     bzero((char *) &serv_addr, sizeof(serv_addr)); //Inicializamos en cero serv_addr, por posibles valores extraños
     serv_addr.sin_family = AF_INET; // Indicamos la familia de la direccion del servidor (AF_INET = IPV4)
     serv_addr.sin_addr.s_addr = INADDR_ANY; //Definimos la dirección del servidor, INADDR_ANY contiene la dirección de la máquina en la que se está ejecutando

     //Hace falta convertir el puerto de host byte order (Que probablemente es Little Endian) a network byte order (Big Endian)
     //Para esto se usa htons y se guarda en sin_port
     serv_addr.sin_port = htons(portno);

     /*
        Ahora asociamos la dirección y puerto al socket.

        bind toma 3 argumentos:

        1. El descriptor de archivo del socket
        2. Un puntero a la dirección a la que se asociará
        3. El tamaño de dicha dirección
     */
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR al asociar");

     /*
        listen() permite al proceso escuchar al socket para esperar conexiones.
        El primer argumento es el descriptor de archivo del socket y el segundo
        la cantidad de conexiones que pueden estar en espera mientras el proceso
        atiende a otra conexión. Por lo general en la mayoría de los sistemas, el
        máximo permitido es 5.
     */
     listen(sockfd,5);
     //clilen guarda el tamaño de cli_addr que se le pasará a accept
     clilen = sizeof(cli_addr);

     /*
        accept() hace que el proceso se bloquee hasta que un cliente se conecte.
        cuando una conexión nueva llega, despíerta nuevamente el proceso.

        Esta llamada al sistema retorna un nuevo descriptor de archivo
        el cual debe ser usado para realizar la comunicación con el cliente como un
        canal bidireccional de lectura/escritura.

        Le entran como parámetros:

        1. El socket en el cual se escucha
        2. un puntero a una estructura el cual contendrá la dirección del cliente
        3. El tamaño de la estructura anterior
     */
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) //Si no se logró hacer la conexión con el nuevo cliente....
          error("ERROR al aceptar");
     //Inicializamos el buffer en 0
     bzero(buffer,256);
     /*
        read() lee lo que el cliente envía (luego de que el cliente hace write)
        a read se le envían como parámetros el descriptor de archivo del socket
        asociado al cliente, el arreglo en el que escribirá lo que envió el cliente
        y la cantidad máxima de caracteres que puede escribir.

        read retorna el número de caracteres leidos y el mensaje enviado por el cliente en el buffer

     */
     n = read(newsockfd,buffer,255);
     if (n < 0)
        error("ERROR al leer del socket");

     printf("El cliente dice: %s\n",buffer);

     //Ahora enviaremos un mensaje al cliente
     printf("Ingrese un mensaje para el cliente: ");
     bzero(buffer,256); //Inicializamos el buffer en 0
     fgets(buffer,255,stdin); //Capturamos el mensaje del usuario

     /*
        write() escribe en el archivo asociado al descriptor de archivos (en este caso envía por el socket)
        a write se le envían como parámetros el descriptor de archivo del socket
        asociado al cliente, el arreglo que se le enviará al cliente
        y la cantidad de caracteres enviados

        write retorna el número de caracteres enviados
     */
     n = write(newsockfd, buffer,strlen(buffer));
     if (n < 0)
        error("ERROR al escribir al socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}

void error(char *msg){
perror(msg); //Imprime un mensaje de error al stderr
    exit(0); //Salimos
}
