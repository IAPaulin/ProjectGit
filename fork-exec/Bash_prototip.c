#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>


#include<stdbool.h>

int main() {
	
	char sep[1]=" "; // массив символов разделителей 
	char m[100];
	char *str;
	int ch;
	int space=0;
	int status;
	int wr,stexe=20;
	
	
	char *ex = "exit\n";
	//bool work=true;
	pid_t pid;
	
	while(1){
		
		printf("write command\n");
		fgets(m,100,stdin);
		str=m;
		

		wr=strcmp(m,ex);
		printf("wr = %d\n",wr);
		if(wr==0){
			//work=false;
			break;
		}
	
		//*****определяем колличество параметров**************
		for(int i=0; ch!='\0'; i++){
			ch = m[i];
			if(ch==' ')
			space++;
		}
		//****************************************************
	
		char *ms[space+1]; // массив строк параметров 
		for(int i=0; i<space+1; i++)
			ms[i]=(char*)malloc(50*sizeof(char));
		ms[space+1]=NULL;
	
	
		//********разбиение строки на колличество параметров***
		ms[0]=strtok(m,sep);
		str=ms[0];
	
		for(int i=1; str!=NULL; i++){
			str = strtok(NULL,sep);
			ms[i]=str;
		} 
		//******************************************************
		printf("***********\n");
	
		pid = fork();
	
		switch(pid){
		
			case -1: 
				perror("fork error \n");
				exit(1);
				break;
		
			case 0:
				/*for(int i=0; i<space+1; i++)
					printf("%s ",ms[i]);*/
				stexe=execv(ms[0],ms);
				if(stexe<0){
				printf("stat execv = %d\n",stexe);
				perror("child\n");
				}
				//execl("test","test","45","4",NULL);
				//execl(ms[0],ms[0],ms[1],ms[2],ms[3],NULL);
				break;
			
			default:
				waitpid(pid,&status,0);
				printf("child end\n");
				printf("status =%d\n", status);
		}
	}
	
	
	printf("dfdf\n");
	
	return 0;
}