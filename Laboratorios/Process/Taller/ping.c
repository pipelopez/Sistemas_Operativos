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
	char *pch;
	struct str_addr addr;
  int aciertos, desaciertos;

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

    pid_t pid_hijo;
    pid_hijo=fork();
    if(pid_hijo==0){
      printf("running host %d\n", init_host+i);
  		addr.host = init_host+i;
  		ans = exec_ping(&addr);//
      exit(ans);
    }
	}

	for(i=0; i<quantity; i++){
    wait(&status);
    if(status==0){
      aciertos++;
    }
  }
  printf("Numero de aciertos %d\n", aciertos);
  /*while (wait(&status)>0) {
    if(WEXITSTATUS(status)==0){
      aciertos++;
    }
  }*/
  desaciertos = quantity-aciertos;
  printf("Numero de desaciertos %d\n", desaciertos);
}

int exec_ping(struct str_addr *_addr){

	FILE *ping_response;
	char ping_comand[100];
	char buffer[100];
	char no_response[] = "0 received";

	sprintf(ping_comand,"ping -w 2 %s.%d",_addr->network,_addr->host);//formato a un string para crear un comando (ping)
	ping_response = popen(ping_comand, "r");//abre un pype para ejecutar un comando en el shell

	while (!feof(ping_response)) {
	  fgets(buffer, 100, ping_response);
	  if (strstr(buffer, no_response)) {//busca un substring
	  		printf("Host %s.%d no response\n\n",_addr->network,_addr->host);
	  		return _addr->host;
	  }
	}
	printf("Host %s.%d response\n\n",_addr->network,_addr->host);
	pclose(ping_response);//cierra la tubería
	return 0;
}
