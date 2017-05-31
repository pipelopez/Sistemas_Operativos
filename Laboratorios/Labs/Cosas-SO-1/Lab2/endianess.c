#include <stdio.h>
#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 0

int endianess(){
	int i = 1;
	char *p = (char *)&i;
	return p[1] == 1 ? LITTLE_ENDIAN : BIG_ENDIAN;
}

int main(){
	if(endianess()){
		printf("big endian\n");
	}else{
		printf("little endian\n");
	}
}