#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*Variable global*/
int x = 0;

void ft(){
  int i;
  printf("Identificador de hilo: %d.\nx tiene el valor de %d\nantes de ser incrementado 1000 veces por este hilo \n", (int)getpid(), x );
  for(i =1; i<=1000; i++) x++;
}

int main(void){
  pthread_t hilos_ids[4];
  int i;
  for(i=0; i<4; ++i){
    pthread_create (&hilos_ids[i], NULL,(void*)ft, NULL);
  }
  for(i=0; i<4; ++i){
    pthread_join(hilos_ids[i], NULL);
  }
  printf("Hilo principal: x=%d\n", x);
  return 0;
}
