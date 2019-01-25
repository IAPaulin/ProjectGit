#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdio.h>

void sig_winch(int signo){

	struct winsize size;
	ioctl(fileno(stdout),TIOCGWINSZ,(char*)&size);
	resizeterm(size.ws_row, size.ws_col);
}

void menu(){
	
	printw("F7 - exit\n");
	printw("F2 - reading file\n");
	printw("F4 - editing file \n");
	printw("\n");
	printw("write comand\n");
}

void setColor(WINDOW *f, int color, char *s){
	
	wattron(f,COLOR_PAIR(color));
	wclear(f);
	wprintw(f,"%s", s);
	wrefresh(f);
}