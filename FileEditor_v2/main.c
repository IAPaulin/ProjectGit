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

void showDir(char *s, WINDOW *w, WINDOW *way);
void createFile(char *s, WINDOW *w);
void openFile(char *s, WINDOW *w);
void copyCh (char *s, WINDOW *w);
void remAll(char *s, WINDOW *w);
void copy (char *s, WINDOW *w);
void help(char *s,WINDOW *w);

char* pasteStr( char *s1, char *s2);
int hashing(char m[]);


int main(){
	
	WINDOW *wnd;
	WINDOW *way;
	WINDOW *swnd;
	WINDOW *sway;
	
	char m1[30];
	char m2[30];
	bool work = true;
	
	// настройка ncurses*************
	initscr();
	cbreak();
	keypad(stdscr,TRUE);
	refresh();
	//*******************************
	
	//создание окон и подокон********
	wnd=newwin(12,50,9,1);
	box(wnd,'|','-');
	swnd=derwin(wnd,10,45,2,2);
	
	way=newwin(5,50,3,1);
	box(way,'*','*');
	sway=derwin(way,2,40,1,1);
	//*******************************
	
	wrefresh(wnd);
	wrefresh(way);
	
	while(work){
		
		scanw("%s%s",m1,m2);
		
		switch( hashing(m1) )
		{
			case 199: //cd
				showDir(m2,swnd,sway);
				move(0,0);   //помещаем курсор в координаты 0,0
				clrtoeol();  // удаление от курсора до конца строки
				break;
				
			case 211:  //cp
				copy(m2,swnd);
				move(0,0);
				clrtoeol();
				break;
				
			case 310: //cpc
				copyCh(m2,swnd);
				move(0,0);
				clrtoeol();
				break;
			
			case 223:  //op
				openFile(m2,swnd);
				move(0,0);
				clrtoeol();
				break;
				
			case 324: //rem
				remAll(m2,swnd);
				move(0,0);
				clrtoeol();
				break;
				
			case 213: //cr
				createFile(m2,swnd);
				move(0,0);
				clrtoeol();
				break;
				
			case 442: //exit
				work=false;
				break;
				
			default:
				help(m1,swnd);
				move(0,0);
				clrtoeol();
				break;
		}
	}
	
	move(0,0);
	clrtoeol();
	
	// удаление окон и подокон*******
	delwin(swnd);
	delwin(sway);
	delwin(wnd);
	delwin(way);
	//*******************************
	
	endwin(); // завершение работы с ncurses
	
	return 0;
	
}
