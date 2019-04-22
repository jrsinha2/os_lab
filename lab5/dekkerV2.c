// Dekker Solution 2 : Using flags for entry and exit (of critical section) for synchronization
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define true 1
#define false 0
int THREAD2,THREAD1;
int x = 0; //shared variable
void *thread1(void* arg)
{	int i =0;
	while(i<5)
	{	while(THREAD2) 
			sleep(1);		//wait till thread2 is executing its critical section
		//enter critical section
		THREAD1 = true;
		printf("Thread1. Shared Variable= %d\n",x);
		x++;
		THREAD1 = false;
		//exit critical section
		i++;
	}
	return NULL;
}
void *thread2(void* arg)
{	int i =0;
	while(i<5)
	{	while(THREAD1) 
			sleep(1);		//wait till thread1 is executing its critical section
		//enter critical section
		THREAD2 = true;
		printf("Thread2. Shared Variable= %d\n",x);
		x++;
		THREAD2 = false;
		//exit critical section
		i++;
	}
	return NULL;
}
int main(int argc,char* argv[])
{	THREAD1 = false,THREAD2 = false;
	pthread_t Thread1,Thread2;
	pthread_create(&Thread1,NULL,thread1,NULL);
	pthread_create(&Thread2,NULL,thread2,NULL);

	pthread_join(Thread1,NULL);
	pthread_join(Thread2,NULL);

	return 0;
}

/*Problems : If threads are preempted (stopped) during flag updation ( i.e during current_thread = true ) 
*			then, both the threads enter their critical section once the preempted thread is restarted, 
*			also the same can be observed at the start itself, when both the flags are false.
*/