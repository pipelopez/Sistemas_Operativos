/*#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int pid;

  if ((pid = fork()) == 0) {
    execl("/bin/ls", "ls", "/", 0);
  }else {
    wait(&pid);
    printf("exec finalizado\n");
  }
  return (0);
}*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
printf("Corriendo ps con execlp\n");
execlp("ps", "ps", "-ax", 0);
printf("Echo.\n");
exit(0);
}
