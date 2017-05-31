#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  pid_t pid;
  char *message;
  int n;

  printf("Llamado a fork\n");
  pid = fork();

  switch(pid) {
    case -1:
    perror("fork falló");
    exit(1);
    case 0:
    message = "Este es el hijo";
    n = 1;
    break;
    default:
    message = "Este es el padre";
    n = 30;
    break;
  }

  for(; n > 0; n--) {
  printf("n=%d ",n);
  puts(message);
  sleep(1);
  }

exit(0);

}
