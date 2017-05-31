#include <pthread.h>
#include <stdio.h>

/*esta estructurira sirve para pasar parámetros a el hilo*/
struct parametros_hilo{
  /*parámetro 1: caracter a imprimir*/
  char caracter;
  /*Parámetro 2: número de veces que se desea imprimir*/
  int contador;
};

/*Esta funcion imprime un número de caracteres a la
salida de error, tal y como la funcion lo indica*/
void* imprimir_caracter (void* parametros){
struct parametros_hilo* p = (struct parametros_hilo*) parametros;
int i;
for (i = 0; i < p-> contador; ++i)
  fputc (p->caracter, stderr);
  return NULL;
}

/*Programa principal*/
int main(){
  pthread_t id_hilo_1;
  pthread_t id_hilo_2;
  struct parametros_hilo hilo1_param;
  struct parametros_hilo hilo2_param;

  /*Crea un hilo para imprimir 30000 x*/
  hilo1_param.caracter = 'x';
  hilo1_param.contador = 30000;
  pthread_create(&id_hilo_1, NULL, &imprimir_caracter, &hilo1_param);

  /*Crea un hilo para imprimir 20000 o*/
  hilo2_param.caracter = 'o';
  hilo2_param.contador = 20000;
  pthread_create(&id_hilo_2, NULL, &imprimir_caracter, &hilo2_param);

  pthread_join (id_hilo_1, NULL);
  pthread_join (id_hilo_2, NULL);

  return 0;
}
