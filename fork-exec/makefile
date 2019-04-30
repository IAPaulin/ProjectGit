
CFLAGS=-c -std=c99 -g -Wall

all: prog

prog:	main.o bash2.o
		gcc main.o bash2.o -o prog	
		rm -rf *.o 	

main.o:	main.c
		gcc $(CFLAGS) main.c

bash.o:	bash.c
		gcc $(CFLAGS) bash2.c


		
