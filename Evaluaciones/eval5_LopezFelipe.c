/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall eval5_LopezFelipe.c -o 1.out -lpthread -lm -lrt
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait()..   */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <pthread.h>        /* sem_init(), sem_post(), sem_wait(), sem_destroy() */
#include <math.h>           /* powf(), sqrtf()          */
#include <string.h>         /* strtok()                 */
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>

/* Definicion de macros y constantes. */

/* Declaracion de funciones. */
int calcularSumaDivisores(int z);
void verificarAmistad(int x, int y, int z, int k);

/* Variables globales. */

/* Main function. */
int main(int argc, char *argv[]) {

    /* Variables locales. */
    int x=0;
    int y =0;
    int suma1 = 0;
    int suma2 = 0;
    sem_t *sem1;
    sem_t *sem2;
    pid_t pid1, pid2, pid3;
    int descriptorMC;
    int *direccionMC;
    int descriptorMC1;
    int *direccionMC1;
    const char *nombreMC = "Mi memoria compartido";
    const char *nombreMC1 = "Mi memoria compartida 1";

    /* Obtener informacion. */
    if (argc != 3) {
            printf("\nError: Numero de parametros invalido.\nDebe iniciar asi: ./1.out <numero1> <numero2>\n");
    		exit(0);
        }
    /* Hacer operaciones. */
    x = atoi(argv[1]);
    y = atoi(argv[2]);

    // COMUNICACION Y SINCRONIZACION
    // -------------------------------------------------------------------------
    descriptorMC=shm_open(nombreMC ,O_CREAT | O_RDWR,0666);
    ftruncate(descriptorMC,sizeof(int));

    direccionMC = (int*)mmap(0, sizeof(int), PROT_READ|PROT_WRITE,MAP_SHARED,descriptorMC,0);
    if(direccionMC== MAP_FAILED){
        return(-1);
    }

    descriptorMC1=shm_open(nombreMC1 ,O_CREAT | O_RDWR,0666);
    ftruncate(descriptorMC1,sizeof(int));

    direccionMC1 = (int*)mmap(0, sizeof(int), PROT_READ|PROT_WRITE,MAP_SHARED,descriptorMC1,0);
    if(direccionMC1== MAP_FAILED){
        return(-1);
    }

    sem1=(sem_t*) mmap(0,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,0);//Se crean lo semaforos en la memoria compartida
    sem2=(sem_t*) mmap(0,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,0);

    sem_init(sem1,1,0);//se inicializa los semaforos
    sem_init(sem2,1,0);//calor del medio diferente a 0, ya que no es hilos

    // Se crean los procesos solicitados: DOS para nuestro caso
    // Se crea el primer proceso hijo
    pid1 = fork();
    if (pid1 < 0) { // Caso de error: No se puede crear un proceso hijo
        printf ("Error: No fue posible crear al primer proceso hijo\n");
        exit(-1);
    } else if(pid1 == 0) { // Primer proceso hijo

        printf("Nuevo proceso (1): Calcular suma de divisores número %d\n", x);
        // Se calcula la suma de divisores del número
        suma1 = calcularSumaDivisores(x);
        printf("Suma1: %d\n", suma1);
        printf("El proceso 1 terminó el cálculo requerido\n" );
        sem_post(sem1); //se indica al otro proceso que este ya termino
        *direccionMC=suma1;//se escribe en la memoria compartida
        exit(0); // <-------------------------- IMPORTANTE

    } else { // Vuelve al proceso padre

        // Se crea el segundo proceso hijo
        pid2 = fork();
        if (pid2 < 0) {
            printf ("Error: No fue posible crear al segundo proceso hijo\n");
            exit(-1);
        } else if (pid2 == 0) { // Segundo proceso hijo
            //sem_wait(sem1);//No realiza operaciones hasta que termine el proceso anterior
            printf("Nuevo proceso (2): Calcular suma de divisores número %d\n", y);
            // Se calcula la suma de divisores del número
            suma2 = calcularSumaDivisores(y);
            printf("Suma2: %d\n", suma2);
            printf("El proceso 2 terminó el cálculo requerido\n");
            sem_post(sem2);//indica al padre no realizar nada hasta que termine
            *direccionMC1=suma2;//se escribe en la memoria compartida
            exit(0); // <-------------------------- IMPORTANTE

        } else { /* Tener en cuenta que al crear proceso (fork) se hace una copia de los semaforos
        por esto se necesita memoria compartida para que los procesos puedan acceder en un
         campo que tengan el mismo valor*/
          // Vuelve al proceso padre
              // Se crea el tercer proceso hijo

              pid3 = fork();
            if (pid3 < 0) {
                printf ("Error: No fue posible crear al tercer proceso hijo\n");
                exit(-1);
            }else if (pid3 == 0) { // Tercer proceso hijo

                sem_wait(sem1);
                sem_wait(sem2);//espera a que termine el proceso 2
                printf("Nuevo proceso (3): Verificar si los números %d y %d son amigos \n", x, y);
                verificarAmistad(x, y, *direccionMC, *direccionMC1);
                printf("El proceso 3 terminó el cálculo requerido\n");

                //sprintf(direccionMC,"%d",suma2);//se escribe en la memoria compartida
                exit(0); // <-------------------------- IMPORTANTE

            }
        }
    }
    shm_unlink(nombreMC);
    shm_unlink(nombreMC1);
    sem_destroy(sem1);//destruyo los semaforos
    sem_destroy(sem2);

    /* Mostrar resultados. */
    //printf("X =%d y=%d\n",x, y );

    return 0;
}

/* Implementacion de funciones. */
int calcularSumaDivisores(int z){
  int suma=0;
  int i;
  for(i=1;i<z;i++)
  {
      if(z%i==0) //La condición es que el numero dividido entre num1 de como resto 0
      {
          suma= suma+i;
      }
  }
  return suma;
}

void verificarAmistad(int x, int y, int z, int k){
  printf("x= %d\n", x);
  printf("y= %d\n", y);
  printf("z= %d\n", z);
  printf("k= %d\n", k);
  if(z==y && k==x){
    printf("Los números %d y %d son números amigos\n", x, y);
  }else{
    printf("Los números %d y %d no son números amigos\n", x, y);
  }
}
