#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0,rcount =0;

void *reader(void *arg)
{
	int r;
	r = ((int)arg);
	
	sem_wait(&mutex);
	rcount++;
	
	if(rcount==1)
		sem_wait(&writeblock);
	
	printf("\n\t%d read by the reader:%d",data,r);
	sem_post(&mutex);
	sleep(1);	
	sem_wait(&mutex);
	
	rcount--;		
	if(rcount==0)
		sem_post(&writeblock);
	sem_post(&mutex);
		
	
}

void *writer(void *arg)
{
	int r;
	r = ((int)arg);
	sem_wait(&writeblock);
	data++;
	printf("\n%d written by the writer:%d",data,r);
	sleep(2);	
	sem_post(&writeblock);	
	

}

main()
{
	int i,b; 
	while(1)
	{ 
	pthread_t rdid[5],wrid[5];
	sem_init(&mutex,0,1);
	sem_init(&writeblock,0,1);
	
	for(i=0;i<3;i++)
	{
		pthread_create(&wrid[i],NULL,writer,(void *)i);
		sleep(1);
		pthread_create(&rdid[i],NULL,reader,(void *)i);
	}

	for(i=0;i<3;i++)
	{
		pthread_join(wrid[i],NULL);
		pthread_join(rdid[i],NULL);
	}
	}

}

  
