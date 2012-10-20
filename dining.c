//Dining Philosophers Problem
//---------------------------------------
/* Sooraj K S
   S5 CSE
   Roll No. 55
   GEC Thrissur */

/* Reference : Modern Operating System ,
               Andrew S.Tanenbaum */
/* You need to compile the program like 'cc file_name.c -lpthread'
and then run it './a.out' */

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
  
#define N 5
#define HUNGRY 1
#define EATING 2
#define THINKING 0
#define LEFT (hpnum+4)%N
#define RIGHT (hpnum+1)%N
  
sem_t mutex;
sem_t S[N];
  
void * philospher(void *num);
void take_fork(int);
void putup_fork(int);
void test(int);
  
int state[N];
int phil_num[N]={0,1,2,3,4};
  
int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
  
void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        putup_fork(*i);
    }
}
  
void take_fork(int hpnum)
{
    sem_wait(&mutex);
    state[hpnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n",ph_num+1);
    test(hpnum);
    sem_post(&mutex);
    sem_wait(&S[hpnum]);
    sleep(1);
}
  
void test(int hpnum)
{
    if (state[hpnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[hpnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n",hpnum+1,LEFT+1,hpnum+1);
        printf("Philosopher %d is Eating\n",hpnum+1);
        sem_post(&S[hpnum]);
    }
}
  
void putup_fork(int hpnum)
{
    sem_wait(&mutex);
    state[hpnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",hpnum+1,LEFT+1,hpnum+1);
    printf("Philosopher %d is thinking\n",hpnum+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}
