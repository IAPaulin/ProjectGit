#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>

void procces(char *s)
{
	char sep[1]=" "; // массив символов разделителей 
	char *str;
	
	int ch;
	int space=0;
	int status,status_exe;
	
	pid_t pid;
	
		//*****определяем колличество параметров**************
		for(int i=0; ch!='\0'; i++){
			ch = *(s+i);
			if(ch==' ')
			space++;
		}
		//****************************************************
	
		char *ms[space+1]; // массив строк параметров 
		ms[space+1]=NULL;
	
		//********разбиение строки на колличество параметров***
		ms[0]=strtok(s,sep);
		str=ms[0];
	
		for(int i=1; str!=NULL; i++){
			str = strtok(NULL,sep);
			ms[i]=str;
		} 
		//******************************************************
		
		pid = fork();
	
		switch(pid)
		{
			case -1: 
				perror("fork error \n");
				exit(1);
				break;
		
			case 0:
				status_exe=execv(ms[0],ms);
				if(status_exe<0){
				perror("child\n");
				}
				break;
			
			default:
				waitpid(pid,&status,0);
				printf("child end\n");
				printf("status =%d\n", status);
		}
}
