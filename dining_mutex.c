//Program Implementing Dining Philosophers Problem Using Mutex and Threads

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

pthread_t philosopher[5];
pthread_mutex_t spoon[5];

void *dine(int n)
{	printf("\nPhilosopher %d is thinking ",n);
	pthread_mutex_lock(&spoon[n]);
	pthread_mutex_lock(&spoon[(n+1)%5]);

	printf("\nPhilosopher %d is eating ",n);
	sleep(1);

	pthread_mutex_unlock(&spoon[n]);
	pthread_mutex_unlock(&spoon[(n+1)%5]);
	printf("\nPhilosopher %d Finished eating",n);
}

void main()
{	int i,err;
	void *msg;

	for(i=1;i<=5;i++)
	{	err=pthread_mutex_init(&spoon[i],NULL);
		if(err!=0)
		{	printf("\n Mutex initialization for spoon failed");
			exit(1);
		}
	}
	for(i=1;i<=5;i++)
	{	err=pthread_create(&philosopher[i],NULL,(void *)dine,(int *)i);
		if(err!=0)
		{	printf("\n Thread creation failed \n");
			exit(1);
		}
	}
	for(i=1;i<=5;i++)
	{	err=pthread_join(philosopher[i],&msg);
		if(err!=0)
		{	printf("\n Thread join failed \n");
			exit(1);
		}
	}

	for(i=1;i<=5;i++)
	{	err=pthread_mutex_destroy(&spoon[i]);
		if(err!=0)
		{	printf("\n Mutex spoon Destroyed \n");
			exit(1);
		}
	}
}
















/*
	OUTPUT
===============

Philosopher 4 is thinking 
Philosopher 4 is eating 
Philosopher 1 is thinking 
Philosopher 1 is eating 
Philosopher 3 is thinking 
Philosopher 2 is thinking 
Philosopher 5 is thinking 
Philosopher 4 Finished eating
Philosopher 3 is eating 
Philosopher 1 Finished eating
Philosopher 5 is eating 
Philosopher 3 Finished eating
Philosopher 2 is eating 
Philosopher 5 Finished eating
Philosopher 2 Finished eating

*/


