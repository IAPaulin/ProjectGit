#include <stddef.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *rot13( const char *src);

int main(){
	
	char *str;
	char mas[100];
	
	
	// Запрос сообщения для кодирования 
	printf("Write string \n");
	fgets(mas,100,stdin);
	str=mas;
	
	
	printf("it is original message %s\n",str); // сообщение до кодирования
	str=rot13(str);  // функция кодирования (шифр Цезаря) 
	printf("it is encrypt message %s\n",str); // сообщение после кодирования
	
	
	free(str);  // Высвобождения ресурсов
	
	return 0;
}

char *rot13( const char *src){
	
	int let,i;
	int counter =0;
	
	
	// Вычисляем количество символов в сообщение
	for(i=0; src[i] != '\0'; i++)
		counter++;
	
	
	// Выделяем память и проводим проверку
	char *str = (char*)malloc((sizeof(char)*counter)+1);
	if(str==NULL)
		return NULL;
	
	
	// Копируем массив символов для проведения кодирования 
	for( i=0; src[i]!='\0'; i++)
	{
		str[i]=src[i];
	}
	
	
	// Выполнения кодирования 
	for(int i=0; str[i] != '\0'; i++)
	{
		let = str[i];
		
		if( (let>=65)&&(let<=90))// Проверяем принадлежность символа к прописным символам
		{  
			let+=13;  // выполняем сдвиг на 13 позиций согласно таблици ASCII
			
			// проверка за выход алфавита, при необходимости создаем круговой сдвиг
			if(let>90)
			{
				let = (let%90)+64;
			}
		}
		else
		{
			if( (let>=97)&&(let<=122) ) // Проверяем принадлежность символа к строчным символам
			{ 
				let+=13;
				if(let>122)
				{
					let = (let%122)+96;
				}
			}
		}
		
		str[i]=let;
	}
	
	return str;
}