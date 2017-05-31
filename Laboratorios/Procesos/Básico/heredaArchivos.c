#include<stdio.h>
#include<error.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  int pid;
  char ch1, ch2;
  fd = open("data.txt", O_RDWR);
  read(fd, &ch1, 1);
  printf("En el padre: ch1 = %c\n", ch1);

  if ((pid = fork()) < 0) {
    perror("fork falló");
    exit(-1); //Sale con código de error
  } else if (pid == 0) {
    read(fd, &ch2, 1);
    printf("En el hijo: ch2 = %c\n", ch2);
  } else {
    read(fd, &ch1, 1);
    printf("En el padre: ch1 = %c\n", ch1);
  }

return 0;
}
