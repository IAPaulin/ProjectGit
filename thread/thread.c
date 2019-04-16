#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>

int shop[5]={100,100,100,100,100};
bool work = true;

pthread_mutex_t lock; // глобальная переменная мьютекс lock


void *load(void *arg);
void *buy(void *arg);


int main(){
	
	pthread_t customer[5],loader;
	
	pthread_mutex_init(&lock,NULL); // инициализация переменной мьютекса
	
	int result;
	int id[5]; // для передачи в поток, адреса. 
	
	for(int i=0; i<5; i++)
	{
		id[i]=i;
		
		result = pthread_create(&customer[i],NULL,buy,&id[i]); // создание n-го покупателя 
		if(result!=0){
			printf("error creating thread %d \n",i);
			exit(1);
		}
	}
	
	result = pthread_create(&loader,NULL,load,NULL);  // создание загрузчика
	if(result!=0){
			printf("error creating thread loader\n");
			exit(1);
		}
		
	// ожидание завершения потока покупателей 
	for(int i=0; i<5;i++)
		pthread_join(customer[i],NULL); 
	//***************************************
	
	work = false; // загрузчик может завершить работу
	
	pthread_join(loader,NULL); // ожидание завершения загрузчика
	
	pthread_mutex_destroy(&lock); // удаление мьютекса
	
	return 0;
}


void *buy(void *arg){
	
	int id = *(int*)arg;
	int mony = 500;
	int spend;
	
	while(mony>0){
		
		pthread_mutex_lock(&lock);  // установка блокировки 
		
		srand(time(NULL));
		spend = rand()%100;
		printf( "spending = %d\n", spend);
		
		if(shop[id]<spend)
			printf("not product, in stock %d for %d customer\n",shop[id],id);
		else{
			
			shop[id]-=spend;
			mony-=spend;
			printf("%d customer buy %d product, balance %d \n",id,spend, mony);
			
		}
		pthread_mutex_unlock(&lock); // снятие блокировки
		sleep(1);
		
	}
	printf( "%d process end\n",id);
	return NULL;
}


void *load(void *arg){
	
	while(work){
		
		for(int i=0; i<5;i++){
			pthread_mutex_lock(&lock);
			
			shop[i]=100;
			printf("%d shop load on 100\n",i );
			
			pthread_mutex_unlock(&lock);
			sleep(2);
		}
		sleep(1);
	}
	printf("work end\n");
	return NULL;
}