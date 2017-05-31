#include <stdio.h>
#include <stdlib.h>

const char FILE_NAME[] = "input.txt";

int main(){
	int count = 0;
	FILE *in_file;

	int ch;
	char inBuf[60];
	in_file = fopen(FILE_NAME, "r");
	if(in_file == NULL){
		printf("cannot open %s\n",FILE_NAME );
		exit(8);
	}

	while(fgets(inBuf,60,in_file)){
		printf("%s\n",inBuf );
		++count;
	}
	printf("Numbers of characters in %s is %d\n",FILE_NAME,count);
	fclose(in_file);
	return(0);
}