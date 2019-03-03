#include <stddef.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int numberWord (char *p);
char** splitString( char *p);
char* movingShift( char* p, int shift);

int main(){
	
	char **m=0;
	
	char *t="I should have known that you would have a perfect answer for me!!!";
	
	m=splitString(t);
	for(int i=0; i<5; i++){
		printf("%s", *(m+i) );
		printf("\n ");
	}
	
	system("clear");
	
	puts(t);
	t=movingShift(t,1);
	puts(t);
	
	m=splitString(t);
	for(int i=0; i<5; i++){
		printf("%s", *(m+i) );
		printf("\n ");
	}
	
	free(m);
	
	return 0;
}


int numberWord (char *p){
	
	unsigned int counterChar=0;
	unsigned int counterWord=0;
	
	// подсчет слов
	for(unsigned int i=0; *(p+i)!='\0'; i++)
	{
		if(*(p+i)=='\n' ||*(p+i)==' ' || *(p+i)=='\t')
			counterChar++;
		else
			counterChar=0;
		
		if(counterChar == 1)
			counterWord++;
	}
	
	return counterWord;
}

char** splitString( char *p){
	
	unsigned int part = numberWord(p)/5 + 1; // сколько слов будет в строке 
	
	unsigned int numberStr=0;
	unsigned int space=0;
	unsigned int word=0;
	unsigned int j=0;
	
	char str[5][20];
	char **mas;
	
	//Создаем массив указателей 
	mas=(char**)malloc(5*sizeof(char*));
	if(mas==NULL)
		return NULL;
	
	// присваиваем каждому указателю массив
	for(int i=0;i<5;i++)
		mas[i]=(char*)malloc(20*sizeof(char));
	
	//чистим массив
	for(int i=0; i<5; i++)
		for(int j=0; j<20;j++)
			str[i][j]=0;
	
		

	// Разбиение строки на 5 подстрок 
	while(numberStr<5) 
	{
		// Выделение подстроки 
		for(int i=0; ; i++, j++)
		{
			if((word==part) || (*(p+j)=='\0'))  
				break;
			
			if(*(p+j)=='\n' ||*(p+j)==' ' || *(p+j)=='\t')
				space++;
			else
				space=0;
			
			if(space == 1)
				word++;
		
			str[numberStr][i] = *(p+j);
		}
		
		mas[numberStr]=str[numberStr];
		numberStr++;
		word=0;
		
		if(*(p+j)=='\0')
			break;
		
	}
	// зачищаем пустые подстроки
	for(int i=numberStr; i<5; i++)
	{
		for(int j=0; j<20;j++)
			str[i][j]=0;
		
		mas[i]=str[i];
	}
	
	return mas;
}

char* movingShift( char* p, int shift){
	
	int sym;
	
	char *str = (char*)malloc(strlen(p)*sizeof(char));
	if(str==NULL)
		return NULL;
	
	//копируем содержимое переданного массива в созданный
	for(int i=0; p[i]!='\0'; i++)
		str[i]=p[i];
	
	//кодирование здесь 
	for(int i = 0; str[i]!='\0'; i++,shift++)
	{
		
		sym=str[i];
		
		if(shift>26)  // что бы не выйти за пределы алфавита 
			shift%=26;
		
		//принадлежность символа к строчной букве 
		if( (sym>=97)&&(sym<=122))
		{
			sym+=shift;
		if(sym>122)
			sym=(sym%122)+96;
		}
		else
		{
		//принадлежность символа к прописной букве 
		if( (sym>=65)&&(sym<=90))
			sym+=shift;
		
		if(sym>90)
			sym=(sym%90)+64;
		}
		
		str[i]=sym;
	}

return str;
}
