// Dekker Solution 1 : Using threadnumber for synchronization
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define THREAD1 0
#define THREAD2 1
int x = 0; //shared variable
int threadNumber;
void startThreads()
{
	threadNumber = rand()%2;
}
void *thread1(void* arg)
{	int i =0;
	while(i<5)
	{	while(threadNumber==THREAD2)		//wait till thread2 is executing its critical section
			sleep(1);
		//enter critical section
		printf("Thread1. Shared Variable= %d\n",x);
		x++;
		threadNumber = THREAD2;
		//exit critical section
		i++;
	}
	return NULL;
}
void *thread2(void* arg)
{	int i =0;
	while(i<5)
	{	while(threadNumber==THREAD1)		//wait till thread1 is executing its critical section
			sleep(1);
		//enter critical section
		printf("Thread2. Shared Variable= %d\n",x);
		x++;
		threadNumber = THREAD1;
		//exit critical section
		i++;
	}
	return NULL;
}
int main(int argc,char* argv[])
{	pthread_t Thread1,Thread2;
	pthread_create(&Thread1,NULL,thread1,NULL);
	pthread_create(&Thread2,NULL,thread2,NULL);

	pthread_join(Thread1,NULL);
	pthread_join(Thread2,NULL);

	return 0;
}

//Problems : Strict Alteration i.e. one process depends on the other process execution, if one process goes infinite then other also goes infinte