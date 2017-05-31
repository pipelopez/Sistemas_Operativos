#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int ejecutar (char* program);

int main (int argc, char *argv[] )
{
  int status;
    printf("Inicia el programa principal\n");

    ejecutar (argv[1]);

    printf ("Finaliza el programa principal\n");
    wait(&status);
    return 0;
}

int ejecutar (char* program)
{
    pid_t child_pid;
    child_pid = fork ();
    if (child_pid > 0){
        wait(NULL);
        printf("Mi hijo finalizo la ejecucion de: %s\n", program);
        return child_pid;
    } else {
        execl (program, program, NULL);
        fprintf (stderr, "Ocurrio un error con execvp: %s\n", program);
        abort ();
    }
}
