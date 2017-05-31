#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc, char* argv[]){
  int spawn(char* programa,char** argumentos){
    pid_t pid_hijo;
    pid_hijo = fork();
    if(pid_hijo!=0){
      //padre
      wait(NULL);
      printf("termino %s", programa);
      return pid_hjo;
    }else{
      //hijo
      return execvp(programa,argumentos);//construye un comando para ejercutarlo en el shell
      fprintf(stderr,"error programa %s\n",programa);
      abort();
    }
  }

  char* argumentos1[]={"gcc",argv[1],"-o",argv[2],NULL};
  char* argumentos2[]={argv[2],NULL};

  spawn(argumentos1[0],argumentos1);
  sleep(4);
  spawn(argumentos2[0],argumentos2);

  return 0;
}
