// Dekker Solution 4 : Using flags for entry and exit (of critical section) for synchronization 
//but to re-ensure mutual exclusion entry flags set before entering section and handle deadlocks
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define true 1
#define false 0
int thread1WantsToEnter,thread2WantsToEnter;
int x = 0; //shared variable

void *thread1(void* arg)
{	int i =0;

	while(i<5)
	{	thread1WantsToEnter = true;
		while(thread2WantsToEnter) 
		{	//printf("Thread1 waiting\n");		//wait till thread2 is executing its critical section
			thread1WantsToEnter = false;		//important order of false and true
			sleep(1);
			thread1WantsToEnter = true;

		}
		//enter critical section
		
		printf("Thread1. Shared Variable= %d\n",x);
		x++;
		thread1WantsToEnter = false;
		//exit critical section
		i++;
	}
	return NULL;
}
void *thread2(void* arg)
{	int i =0;
	while(i<5)
	{	thread2WantsToEnter = true; 
		while(thread1WantsToEnter) 
		{	//printf("Thread 2 waiting\n");		//wait till thread1 is executing its critical section
			thread2WantsToEnter = false;
			sleep(1);
			thread2WantsToEnter = true;
		}
		//enter critical section
		
		printf("Thread2. Shared Variable= %d\n",x);
		x++;
		thread2WantsToEnter = false;
		//exit critical section
		i++;
	}
	return NULL;
}
int main(int argc,char* argv[])
{	thread1WantsToEnter = false,thread2WantsToEnter = false;
	
	pthread_t Thread1,Thread2;
	pthread_create(&Thread1,NULL,thread1,NULL);
	pthread_create(&Thread2,NULL,thread2,NULL);

	pthread_join(Thread1,NULL);
	pthread_join(Thread2,NULL);

	return 0;
}
