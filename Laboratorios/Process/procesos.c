#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void){
  long ID1, ID2;
  ID1 = syscall (SYS_getpid);
  printf("syscall (SYS_getpid)=%1d\n", ID1);
  ID2= getpid();
  printf("getpid()=%1d\n", ID2);
  return 0;
}
