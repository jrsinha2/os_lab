#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<limits.h>
#define N 10
int choosing[N];
int tickets[N];
int maxValue()
{	int mx = INT_MIN;
	int i;
	for(i =0;i<N;i++)
	{	if(tickets[i]>mx)
			mx = tickets[i];
	}
	return mx;
}
void* thread(void* arg)
{	int* p = (int*)arg;
	int x = *p;		//ProcessNumber()
	printf("%d\n",x);
	int done = 0;
	int i;
	while(!done)
	{	choosing[x]=1;
		tickets[x] = maxValue()+1;		
		choosing[x] = 0;
		for(i=0;i<N;i++)
		{	if(i==x)
				continue;
			while(choosing[i]!=0)
				;
			while(tickets[i] != 0 && tickets[i] < tickets[x])
				;
			if(tickets[i]==tickets[x] && i<x)
			{	while(tickets[i]!=0)
				;
			}
		}
		tickets[x]=0;
		done = 1;
	}
	return NULL;
}
int main()
{	pthread_t t[N];
	int arr[N];
	int i;
	for(i =0;i<N;i++)
	{	arr[i]=i;
		choosing[i]=0;
		tickets[i]=0;
	}
	for(i =0;i<N;i++)
	{	int *p = &arr[i];
		pthread_create(&t[i],NULL,thread,(void*)p);
	}
	for(i =0;i<N;i++)
	{	pthread_join(t[i],NULL);
	}
	return 0;
}
