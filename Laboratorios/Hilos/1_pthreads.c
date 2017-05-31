/*
	Example: Creating threads
	compile: gcc -o threads 1_threads.c -lpthread
	To execute: ./threads
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	pthread_t tid; /* the thread identifier */
	int value;

	if (argc !=2){
		printf("Recuerde escribir el número de parámetros válido\n" );
		exit(0);
	}

	value= atoi (argv[1]);

	/* create the thread */
	pthread_create(&tid, NULL, runner, (void *)&value);
	/* wait for the thread to exit */
	pthread_join(tid, NULL);//equivalente de wait, si se comenta no hace la suma.

	printf("sum = %d\n",sum);
	return 0;

}

/* The thread will begin control in this function */
void *runner(void *arg)
{
	int i, upper = *((int *)arg);
	sum = 0;
	for (i = 1; i <= upper; i++)
		sum += i;

	pthread_exit(0);
}
