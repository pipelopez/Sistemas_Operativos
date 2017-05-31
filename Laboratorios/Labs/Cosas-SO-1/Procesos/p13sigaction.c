#include <stdio.h>
//Contiene lo necesario para poder especificar como el programa maneja señales mientras se ejecuta
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void my_handler (int sig);

int main(void){
	struct sigaction my_action;

	/*Catch sigint*/

	my_action.sa_handler = my_handler;
	my_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &my_action, NULL);
	printf("catching SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");

	//Ignore sigint

	my_action.sa_handler = SIG_IGN;
	my_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &my_action, NULL);
	printf("ignoring SIGINT\n");
	sleep(3);
	printf("Sleep is over\n");

	my_action.sa_handler = SIG_DFL;
	my_action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &my_action, NULL);
	printf("default SIGINT\n");
	sleep(3);
	printf("NO SIGINT WITHIN 3 SECONDS\n");
}

void my_handler(int sig){
	printf("I got SIGINT, number %d\n", sig);
	exit(0);
}