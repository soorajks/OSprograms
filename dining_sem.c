//Program implementing Dining Philosophers Problem Using Semaphores and Forks

#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>

sem_t *sem[20];

void philosopher(int val)
{
	printf("Philosopher %d Thinking\n",val+1);
	
	while(1)
	{
		sem_wait(sem[val%5]);
		if(!sem_trywait(sem[(val+1)%5]))
			break;
		else
			sem_post(sem[val%5]);
	}

	printf("\tPhilosopher %d Eating\n",val+1);
	sleep(2);
	sem_post(sem[val%5]);
	sem_post(sem[(val+1)%5]);
	
	printf("\t\tPhilosopher %d Finished Eating\n",val+1);

}

void main()
{
	pid_t cpid[5];
	char semname[5];
	int i=0;
	
	for(i=0;i<5;i++)
	{	
		sprintf(semname,"%d",getpid()+i);
		
		sem[i]=sem_open(semname,O_CREAT|O_EXCL,0666,1);
		
		if(sem[i]==SEM_FAILED)
			perror("Unable to create semaphore");

	}
	for(i=0;i<5;i++)
	{
		cpid[i]=fork();
		if(cpid[i]==0)
			break;

	}
	if(i==5)
	{
		int status;
		for(i=0;i<5;i++)
			waitpid(cpid[i],&status,WUNTRACED);
		
		for(i=0;i<5;i++)
		{	sem_close(sem[i]);
			sprintf(semname,"%d",getpid()+i);
			sem_unlink(semname);
		}
	}
	else
		philosopher(i);

}

/*
	OUTPUT
===============

Philosopher 1 Thinking
Philosopher 2 Thinking
	Philosopher 2 Eating
Philosopher 4 Thinking
	Philosopher 4 Eating
Philosopher 3 Thinking
Philosopher 5 Thinking
	Philosopher 1 Eating
		Philosopher 2 Finished Eating
	Philosopher 3 Eating
		Philosopher 4 Finished Eating
	Philosopher 5 Eating
		Philosopher 1 Finished Eating
		Philosopher 3 Finished Eating
		Philosopher 5 Finished Eating

*/



