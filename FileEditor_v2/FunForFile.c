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



void openFile(char *s, WINDOW *w)
{
	werase(w);
	
	keypad (w, TRUE); // для приема F3
	
	FILE *fl;
	
	int numStr=1;
	int ch;
	
	//открытие файла на чтение и запись*********
	fl = fopen(s,"r+");
	if(fl==NULL){
		wprintw(w,"Error opening file %s",s);
		wrefresh(w);
		return;
	}
	//******************************************
	
	// чтение файла ***************************
	while(!feof(fl)){
		
		ch=fgetc(fl);
		if(ch=='\n')
			numStr++;
		waddch(w,ch);
	}
	//******************************************
	wrefresh(w); // обновление экрана
	
	move(0,0);
	clrtoeol();
	
	printw("Press F3 for save and exit");
	refresh();
	
	// запись данных в файл *******************
	while( (ch=wgetch(w))!=KEY_F(3))
	{
		if(ch=='\n'){
			wmove(w,numStr,0);
			numStr++;
		}
		fprintf(fl,"%c",ch);
	}
	//******************************************
	
	fclose(fl);
}



void copy (char *s, WINDOW *w)
{
	werase(w);
	
	FILE *florig;
	FILE *flout;
	
	char buffer[100];
	
	// открываем копируемый файл для чтения*****
	florig = fopen(s,"r");
	if(florig==NULL){
		wprintw(w,"Error opening file %s",s);
		wrefresh(w);
		return;
	}
	//******************************************
	
	wprintw(w,"Write way for coping\n");
	wrefresh(w);
	
	move(0,0);
	clrtoeol();
	
	getstr(buffer); // считываем путь куда для копирования
	
	// создаем  файл***************************
	flout = fopen(buffer,"w+");
	if(flout==NULL){
		wprintw(w,"Error opening file on writing\n");
		wrefresh(w);
		return;
	}
	//******************************************
	
	// копирование содержимого в новый файл*****
	while(!feof(florig)){
		
		if(fgets(buffer,99,florig))          
			fprintf(flout,"%s",buffer);
	}
	//******************************************
	
	wprintw(w,"coping end\n");
	wrefresh(w);
	
	fclose(florig);
	fclose(flout);
}



void showDir(char *s, WINDOW *w, WINDOW *way)
{
	werase(w);
	werase(way);
	
	wprintw(way,"%s",s);
	wrefresh(way);
	
	DIR *dir;
	struct dirent *entry;
	
	//открытие директории и проверка***********
	dir=opendir(s);
	if(dir==NULL){
		perror("dir not open");
		return;
	}
	//******************************************
	
	// вывод содержимого каталога***************
	while( (entry=readdir(dir)) !=NULL){
		
		wprintw(w,"%s\n", entry->d_name);
		wrefresh(w);
	}
	//******************************************
	
	closedir(dir);
}



void createFile(char *s, WINDOW *w)
{
	werase(w);
	
	FILE *fl;
	
	fl=fopen(s,"a+");
	if(fl==NULL){
		wprintw(w,"error when create file\n");
		wrefresh(w);
	}
	else{
		wprintw(w,"create file\n");
		wrefresh(w);
	}
	
	fclose(fl);
}



void copyCh (char *s, WINDOW *w) // копирование по символьно
{
	
	werase(w);
	
	FILE *florig;
	FILE *flout;
	
	char buffer[100];
	int ch;
	
	// открываем копируемый файл для чтения*****
	florig = fopen(s,"r");
	if(florig==NULL){
		wprintw(w,"Error opening file %s",s);
		wrefresh(w);
		return;
	}
	//******************************************
	
	wprintw(w,"Write way for coping\n");
	wrefresh(w);
	
	move(0,0);
	clrtoeol();
	
	getstr(buffer);
	
	// создаем  файл***************************
	flout = fopen(buffer,"w+");
	if(flout==NULL){
		wprintw(w,"Error opening file on writing\n");
		wrefresh(w);
		return;
	}
	//******************************************
	
	// копирование содержимого в новый файл*****
	while(!feof(florig)){
	
		ch = fgetc(florig);
		fputc(ch,flout);
	}
	//******************************************
	
	wprintw(w,"coping end\n");
	wrefresh(w);
	
	fclose(florig);
	fclose(flout);
}



void remAll(char *s, WINDOW *w){
	
	werase(w);
	
	DIR *dir;
	
	struct dirent *de;
	struct stat buf;
	
	int result;
	char *str;
	
	result = stat(s,&buf);
	
	if(result != 0)
		wprintw(w,"Error stat\n");
	
	if(S_ISREG(buf.st_mode)) // если файл это файл
	{
		if(0==remove(s)){
				wprintw(w,"file delete\n");
				wrefresh(w);
		}
		return ; 
	}
	else
	{
		if(S_ISDIR(buf.st_mode))
		{
			
		//открытие директории и проверка***********
		dir=opendir(s);
		if(dir==NULL){
			perror("dir not open");
			return ;
		}
		//******************************************
		
		// считываем содержимое директории и удаляем файлы*****
		while( (de=readdir(dir))!=NULL){
		
			str=de->d_name;
			str=pasteStr(s,str); // для сохранения пути
			
			result = stat(str,&buf);
			if(result != 0)
				wprintw(w,"Error stat\n");
			
			/*if(S_ISDIR(buf.st_mode))  
				remAll(str,w);*/
		
			remove(str);
		}
		//******************************************************
		
		if(0==remove(s)) //удаление самой директории
		{
			wprintw(w,"file delete\n");
			wrefresh(w);
		}
	
		closedir(dir);
		}
	}
}
