#include <pthread.h>
#include <stdio.h>

void* calcular_primo (void* arg);

int main(){
  pthread_t hilo_id;
  int cual_primo =5000;
  int primo;

  /*Inicia el hilo, se requiere el 5000-ésimo número primo. */
  pthread_create (&hilo_id, NULL, calcular_primo, &cual_primo);
  /*Puedo hacer algo mientras... si quiero*/
  /*Espero que el número sea calculado y me sea entregado*/
  pthread_join(hilo_id, (void**) &primo);
  /*imprimo el número entregado*/
  printf("El númreo primo es %d\n", primo);
  return 0;
}

/*Calcula los números primos sucesivamente
retorna el N-ésimo número primo, donde N es el valor apuntado por *ARG*/
void* calcular_primo(void* arg){
  int candidato =2;
  int n = *((int*)arg);
  while (1) {
    int factor;
    int es_primo= 1;
    for(factor=2; factor<candidato; ++factor){
      if (candidato%factor ==0) {
        es_primo=0;
        break;
      }
      if (es_primo) {
        if (--n ==0) {
          return (void*) candidato;
        }
      }
        ++candidato;
    }
  }
  return NULL;
}
