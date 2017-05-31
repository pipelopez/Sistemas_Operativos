#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void){
	long ID1, ID2;
	ID1 = syscall(SYS_getpid);
	ID2 = getpid();
	printf("syscall: %d, getpid: %d",ID1,ID2);
}