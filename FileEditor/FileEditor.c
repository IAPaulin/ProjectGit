#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdio.h>

void sig_winch(int signo);
void readFile(WINDOW *wnd, WINDOW *f);
void writeFile(WINDOW *wnd, WINDOW *f4,WINDOW *f3);
void copyFile(WINDOW *wnd, WINDOW *f);
void setColor(WINDOW *f, int color, char *s);
void menu();

int main (int argc, char **argv){
	
	//*******Настройка работы с ncurses*****
	initscr();
	signal(SIGWINCH,sig_winch);
	keypad(stdscr,TRUE);
	refresh();
	start_color();
	//***************************************
	
	//*******Создание рабочих окон **********
	WINDOW *wnd;
	WINDOW *f2;
	WINDOW *f4;
	WINDOW *f5;
	WINDOW *f3;
	WINDOW *f7;
	
	wnd = newwin(25,25,6,4);
	f2 = newwin(1,10,8,30);
	f4 = newwin(1,10,10,30);
	f5 = newwin(1,10,12,30);
	f3 = newwin(1,20,14,30);
	f7 = newwin(1,10,16,30);
	//****************************************
	
	//*******Настройка цвета*******
	init_pair(1,COLOR_RED, COLOR_WHITE);
	init_pair(2,COLOR_RED, COLOR_GREEN);
	
	box(wnd,'*','*');  //делает рамку окна wnd
	
	wattron(f2,COLOR_PAIR(1));
	wattron(f4,COLOR_PAIR(1));
	wattron(f5,COLOR_PAIR(1));
	wattron(f3,COLOR_PAIR(1));
	wattron(f7,COLOR_PAIR(1));
	wprintw(f2,"F2-read");
	wprintw(f4,"F4-write");
	wprintw(f5,"F5-copy");
	wprintw(f3,"F3-save and closes");
	wprintw(f7,"F7-exit");
	
	wrefresh(wnd);
	wrefresh(f2);
	wrefresh(f4);
	wrefresh(f5);
	wrefresh(f3);
	wrefresh(f7);
	//*********************************************
	
	int ch = 0;
	bool work=true;
	char *str = "F5-exit";
	
	printw("Programma for editing file\n");
	menu();
	
	while(work){
		
		ch = getch();
		
		switch(ch){
		
			case KEY_F(2):
				
				readFile(wnd,f2);
				break;
				
				
			case KEY_F(4):
				
				writeFile(wnd,f4,f3);
				break;
			
			case KEY_F(5):
				
				copyFile(wnd,f5);
				break;
			case KEY_F(7):
				setColor(f7,2,str);
				work = false;
				
		}
		
		wclear(wnd);
	
	}
	
	//*******Освобождение ресурсов*******
	delwin(wnd);
	delwin(f2);
	delwin(f4);
	delwin(f5);
	delwin(f3);
	delwin(f7);
	//***********************************
	
	move(11,0);
	printw("Press anu key\n");
	
	refresh();
	getch();
	endwin();
	
	return 0;
}

