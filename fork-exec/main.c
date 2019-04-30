#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>


void procces(char *s);

int main() {
	
	char *s;
	char m[100];
	char *ex="exit\n";
	
	while(1)
	{
		printf("write command\n");
		fgets(m,100,stdin);
		s=m;
		
		if(0==strcmp(m,ex)){
			break;
		}
		procces(s);
		printf("\n");
	}
	
	return 0;
}