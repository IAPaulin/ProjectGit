#include<termios.h>
#include<signal.h>
#include<stdlib.h>
#include<curses.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<unistd.h>



char* pasteStr( char *s1, char *s2){
	
	int ln1 = strlen(s1);
	int ln2 = strlen(s2);
	int ln = ln1+ln2;
	int j=0;
	
	char *str = (char*)malloc(sizeof(char)*ln+2);
	
	// копирование первой строки в исходную ****
	for(int i=0; *(s1+i)!='\0'; i++){
		*(str+i)=*(s1+i);
		j++;
	}
	//******************************************
	
	*(str+j)='/';
	j++;
	
	// копирование второй строки в исходную ****
	for(int i=0; *(s2+i)!='\0'; i++){
		*(str+j)=*(s2+i);
		j++;
	}
	//******************************************
	
	return str;
}



int hashing(char m[])
{
	int hash=0;
	
	for(int i=0; m[i]!='\0'; i++){
		hash+=m[i];
	}
	return hash;
}



void help(char *s, WINDOW *w)
{
	werase(w); // отчистка окна w
	
	wprintw(w,"not command %s\n",s);
	
	wprintw(w,"cd - change the directory\n");
	wprintw(w,"cp - copying the file through buffer\n");
	wprintw(w,"cpc - copying the file through char\n");
	wprintw(w,"op - opening the file\n");
	wprintw(w,"rem - delete the file or girectory\n");
	wprintw(w,"cr - creation the file\n");
	wprintw(w,"exit - exit from programm\n");
	wrefresh(w);
}
