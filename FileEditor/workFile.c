#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdio.h>


void readFile(WINDOW *wnd, WINDOW *f){
	
	FILE *fl;
	int ch =0;
	char name[100];
	char *str = "F2-read";
	
	setColor(f,2,str);
	
	wprintw(wnd,"write file name\n");
	wgetnstr(wnd,name,99);
	
	//*******Открытие файла на чтение и проверка*******
	fl = fopen(name,"r");
	
	if(fl==NULL){
		wprintw(wnd,"Error open file\n");
		wrefresh(wnd);
		setColor(f,1,str);
		return;
	}
	//**************************************************
	
	wprintw(wnd,"open file\n");
	
	//*******Чтение файла**************
	while(!feof(fl)){
		
		ch=fgetc(fl);
		wprintw(wnd,"%c",ch);
	}
	//*********************************
	
	wrefresh(wnd);
	wprintw(wnd,"\n");
	
	setColor(f,1,str);
	
	fclose(fl);
}

void writeFile(WINDOW *wnd, WINDOW *f4,WINDOW *f3){

	keypad (wnd, TRUE);
	
	FILE *fl;
	int ch =0;
	char name[100];
	char *strW = "F4-write";
	char *strS = "F3-save and closes";
	
	setColor(f4,2,strW);
	
	wprintw(wnd,"write file name\n");
	wgetnstr(wnd,name,99);
	
	//*******Открытие файла на запись и проверка*******
	fl=fopen(name,"a+");
	
	if(fl==NULL){
		wprintw(wnd,"Error open file\n");
		wrefresh(wnd);
		setColor(f4,1,strW);
		return;
	}
	//**************************************************
	
	//*******Процесс записи************************
	wprintw(wnd,"Press F3 for save and close\n");
	while(1){
		ch = wgetch(wnd);
		
		if(ch == KEY_F(3)){
		    setColor(f3,2,strS);
		    break;
		}
		wrefresh(wnd);
		fputc(ch,fl);
		
	}
	//***********************************************
	wprintw(wnd,"\n");
	getch();
	
	setColor(f3,1,strS);
	setColor(f4,1,strW);
	
	fclose(fl);
}

void copyFile(WINDOW *wnd, WINDOW *f){
	
	FILE *flin;
	FILE *flout;
	int ch;
	int i;
	char name[100];
	char *str = "F5-copy";
	
	setColor(f,2,str);
	
	wprintw(wnd,"write file name\n");
	wgetnstr(wnd,name,99);
	
	
	//*******Открытие копируемого файла******************** 
	flin = fopen(name,"r");
	
	if(flin==NULL){
		wprintw(wnd,"Error open file on read\n");
		wrefresh(wnd);
		setColor(f,1,str);
		return;
	}
	//******************************************************
	
	for(i=0;i<100;i++) // Зачистка строки 
		name[i]=' ';
	
	
	wprintw(wnd,"write coping file name\n");
	wgetnstr(wnd,name,99);
	
	//*******Создание копии файла****************************
	flout = fopen(name,"w+");
	
	if(flout==NULL){
		wprintw(wnd,"Error open file on write\n");
		wrefresh(wnd);
		setColor(f,1,str);
		fclose(flin);
		return;
	}
	//********************************************************
	
	//*******Копирование************
	while(!feof(flin)){
	
		
		ch = fgetc(flin);
		fputc(ch,flout);
	}
	//******************************
	
	wprintw(wnd, "coping end\n");
	wrefresh(wnd);
	
	setColor(f,1,str);
	
	fclose(flin);
	fclose(flout);
}