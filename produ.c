#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
pthread_t t[4];
sem_t full,empty,lock;
int getid()
{
    int i;
    for(i=0;i<5;i++)
        if(pthread_equal(pthread_self(),t[i]))
            return i;
}
void *start(void *arg)
{
    while(1)
    {
        int mode=(int)arg;
        sem_wait(&lock);
        int id=getid();
        sem_post(&lock);
        int i=0;
        if(mode==0)
        {
            sem_wait(&full);
            printf("\t %d consumes \n",id);
            sem_post(&empty);
            sleep(1);
        }
        else
        {
            sem_wait(&empty);
            printf("%d produces \n",id);
            sem_post(&full);
            sleep(1);
        }
    }
}
int main()
{
    int i=0;
    sem_init(&full,0,0);
    sem_init(&empty,0,10);
    sem_init(&lock,0,1);
    pthread_create(&t[0],NULL,start,(void *)i);
    pthread_create(&t[1],NULL,start,(void *)i);
    pthread_create(&t[2],NULL,start,(void *)i);
    pthread_create(&t[3],NULL,start,(void *)i+1);
    for(i=0;i<4;i++)
        pthread_join(t[i],NULL);
    return 0;
}
