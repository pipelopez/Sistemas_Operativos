#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

struct str_addr{
    char network[15];
    int host;
};

//declaracion funciones
int exec_ping();

int main(int argc, char* argv[])
{
	pid_t pid;
	int status, i;
	int ans;
	int init_host, quantity;
	double resp,noResp;

	char *pch;
	struct str_addr addr;
		
	if(argc != 3){
		printf("error arguments\n");
		printf("./a.out <network> <quantity> \n");
		printf("%s 192.168.0.10 5\n", argv[0]);
		exit(1);
	}
	
	pch=strrchr(argv[1],'.');		//Busca el ultimo punto y  
	*pch = '\0';						//lo reemplaza por el caracter nulo
	init_host = atoi(pch+1);
	strcpy(addr.network, argv[1]);
	quantity = atoi(argv[2]);
	
	printf("network %s\n", addr.network);
	printf("host %d\n\n", init_host);
	
	for(i=0; i<quantity; i++){
		if((pid = fork()) == 0){ // Si es el hijo
			printf("Child running %d\n", init_host+i);
			addr.host = init_host+i;
			exit(exec_ping(&addr));
		}
	}
	ans = 0;
	for(i=0; i<quantity; i++){
		wait(&status);
		ans = ans + WEXITSTATUS(status);
	}
	noResp = ((double)ans/quantity)*100.0f;
	resp = 100.0f-noResp;
	printf("\nPorcentaje de máquinas que respondieron: %0.1f %%\n", resp );
	printf("Porcentaje de máquinas que NO respondieron: %0.1f %% \n", noResp );
	printf("End parent\n");
}


/**
*	Explicación exec_ping:

*	El método exec_ping recibe como parametro el apuntador a una  
*	estructura de tipo str_addr que tiene un arreglo de caracteres 
*	donde se almacenan los primeros 3 bytes de la dirección (usando la 
*	notación 'dot-decimal' (punto-decimal)), adicionalmente contiene un 
*	entero que representa el último byte de la dirección a la que se 
*	le hará el ping.
*/
int exec_ping(struct str_addr *_addr){
	//Aquí se declara un apuntador a un 'fichero', que a fin de cuentas
	//nos servirá para recorrer el resultado del comando ping
	FILE *ping_response;

	//En ping_comand se almacenará el comando que se ejecutará para hacer el ping
	char ping_comand[100];

	//En buffer se irá almacenando cada linea leída del resultado de ejecutar
	//el comando que hará el ping
	char buffer[100];

	//no_response es una cadena de caracteres la cual será buscada en cada linea
	//del comando ping, si se encuentra quiere decir que el ping NO fue exitoso.
	char no_response[] = "0 received";

	//sprintf se usa para 'escribir' en un string dando un formato en particular
	//En este caso, se usa para ensamblar las partes necesarias que compondrán
	//el comando ensamblado resultará así: 'ping -w 2 192.168.1.1'
	//donde el parámetro -w 2 indica que el programa (ping) debe finalizar
	//a los 2 segundos luego de haberse iniciado y el segundo parámetro
	//es la dirección IP que se construyó desde la estructura _addr
	sprintf(ping_comand,"ping -w 2 %s.%d",_addr->network,_addr->host);

	//con popen se crea un nuevo proceso por medio de un pipe y 
	//en él se ejecuta el comando almacenado en ping_comand,
	//el parámetro "r" indica que el pipe es para recibir (leer)
	//la información.
	//en este caso popen retornará un apuntador a un "FILE" que contendrá
	//lo arrojado por la salida estandar del comando ejecutado.
	ping_response = popen(ping_comand, "r");
	
	//mientras no se haya llegado al final del resultado del comando...
	while (!feof(ping_response)) {
	  //copie en buffer la siguiente linea del resultado del comando (o hasta que lea 100 caracteres)
	  fgets(buffer, 100, ping_response);

	  //revise si en buffer está la cadena '0 received'
	  if (strstr(buffer, no_response)) {
	  	    //Si está la cadena, quiere decir que el host no respondió a ninguno
	  		//de los paquetes enviados por el comando ping, indiquele al usuario la situación
	  		printf("Host %s.%d no response\n",_addr->network,_addr->host);
	  		//salga de la función retornando un valor diferente de 0 que indica que falló.
	  		return 1;
	  }
	}
	//Si al final de leer el resultado no encuentra '0 received' quiere decir que recibió
	//al menos una respuesta por lo cual podemos decir que está vivo.
	//Y le indicamos eso al usuario
	printf("Host %s.%d response\n",_addr->network,_addr->host);

	//pclose espera que finalice el proceso asociado a ping_response y cierra el steam
	pclose(ping_response);
	return 0;
}
