// Fuente original: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

#include <stdio.h> //IO básica
#include <sys/types.h> //Definiciones de varios tipos de datos usados en llamadas al sistema
#include <sys/socket.h> // Lo necesario para usar sockets
#include <netinet/in.h> // Contiene lo necesario para conexiones por internet
#include <stdlib.h> // Librería estandar
#include <string.h> //para fgets
#include <unistd.h> //Constantes y tipos variados
#include <netdb.h> //Define la estructura hostent

void error(char *msg); //Lo usamos para imprimir los posibles errores



/*
Código del cliente para una conexión entre procesos usando sockets.
Una explicación más amplia de todas las funciones y llamadas al sistema
se encuentra en el código del servidor
*/
int main(void){
    int sockfd; //Aquí se guarda el descriptor de archivo del socket
    int portno = 50000; //Puerto del servidor
    struct sockaddr_in serv_addr;
    struct hostent *server; //Guardará la información relacionada a la dirección en internet del servidor
    int n;// Guardará el número de caracteres leidos o escritos
    char buffer[256]; //Buffer donde guardaremos los mensajes de entrada
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //Creamos el socket, info más detallada en el código del servidor
    if (sockfd < 0) //Si existe un problema...
        error("ERROR abriendo el socket");
    //Gethostbyname se encarga de retornar la dirección IP de un host determinado
    server = gethostbyname("localhost");
    if (server == NULL) { //Si hubo un problema....
        fprintf(stderr,"ERROR, no existe dicho host\n");
        exit(0);
    }

    //Inicializamos en 0 serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // Indicamos que la familia de direcciones del servidor es IPv4

    //Copiamos la direccion del servidor almacenada en server->h_addr
    //a serv_addr
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    //Hace falta convertir el puerto de host byte order a network byte order
    //Para esto se usa htons y se guarda en sin_port
    serv_addr.sin_port = htons(portno);
    /*
        Usamos connect para conectarnos al servidor, connect espera 3 parámetros
        1. El descriptor de archivo del socket usado para conectarse al servidor
        2. La información del host al que se desea conectar (IP y puerto)
        3. el tamaño de serv_addr
    */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR conectandose al servidor");
    printf("Ingrese el mensaje que será enviado al servidor: ");
    bzero(buffer,256); //Inicializamos el buffer en 0
    fgets(buffer,255,stdin); //Recibimos la entrada del usuario

    // Write envía el contenido del buffer por el socket y retorna la cantidad de caracteres enviados
    //(Más info en el código del servidor
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)//Si write no tuvo éxito...
         error("ERROR escribiendo al socket");
    bzero(buffer,256); //Inicializamos el buffer en 0
    //read() lee lo que el servidor envía y retorna el número de caracteres enviados
    //(Más info en el código del servidor)
    n = read(sockfd,buffer,255);
    if (n < 0)
         error("ERROR leyendo desde el socket");
    printf("El servidor dice: %s",buffer);
    close(sockfd);
    return 0; // Salimos
}

void error(char *msg){
    perror(msg); //Imprime un mensaje de error al stderr
    exit(0); //Salimos
}
