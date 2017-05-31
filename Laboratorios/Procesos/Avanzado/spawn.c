/*#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

int spawn(char* programa,char** argumentos);
int main(int argc, char* argv[]){


  char* argumentos1[]={"gcc",argv[1],"-o",argv[2],NULL};
  char* argumentos2[]={argv[2],NULL};

  spawn(argumentos1[0],argumentos1);
  sleep(4);
  spawn(argumentos2[0],argumentos2);

  return 0;
}

int spawn(char* programa,char** argumentos){
  pid_t pid_son;
  pid_son = fork();
  if(pid_son!=0){
    //padre
    wait(NULL);
    printf("\ntermino %s\n", programa);
    return pid_son;
  }else{
    //hijo
    return execvp(programa,argumentos);//construye un comando para ejercutarlo en el shell
    fprintf(stderr,"\nerror programa %s\n",programa);
    abort();
  }
}*/

// gcc spawn_sol.c -o spawner
// ./spawner programa.c ./programa

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int spawn (char* program, char** arg_list);

int main (int argc, char *argv[] )
{
    printf("Inicia el programa principal\n");

  char* arg_list[] = {    // gcc programa.c -o ./programa
        "gcc",argv[1],
        "-o",
        argv[2],
        NULL
    };

    char programa2[14]="./";
    strcat(programa2, argv[2]);
    printf("Programa2: %s\n",(char*)programa2 );

    char* arg_list2[] = {   // ./programa
        argv[2],
        NULL
    };

    spawn (arg_list[0], arg_list);
    sleep(2);
    spawn (programa2, arg_list2);

    printf ("Finaliza el programa principal\n");

    return 0;
}

int spawn (char* program, char** arg_list)
{
    pid_t child_pid;
    child_pid = fork ();
    if (child_pid > 0){
        wait(NULL);
        printf("Mi hijo finalizo la ejecucion de: %s\n", program);
        return child_pid;
    } else {
        execvp (program, arg_list);
        fprintf (stderr, "Ocurrio un error con execvp: %s\n", program);
        abort ();
    }
}
