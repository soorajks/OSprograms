//Sleeping Barber Problem
//---------------------------------------
/* Sooraj K S
   S5 CSE
   Roll No. 55
   GEC Thrissur */

/* Reference : Modern Operating System ,
               Andrew S.Tanenbaum */
/* You need to compile the program like 'cc file_name.c -lpthread'
and then run it './a.out' */

#include <stdio.h>

#include<pthread.h>

#include <stdlib.h>

#define seats 6 /*chairs for waiting customers*/

void *customer();
void *barberShop();
void *waiting_Room();
void checkQueue();

pthread_mutex_t queue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wait = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sleepa = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barberSleep = PTHREAD_COND_INITIALIZER;
pthread_cond_t barberWorking = PTHREAD_COND_INITIALIZER;

int returnTime=5,current=0,urakam =0, asdfgh;

int main(int argc, char *argv[])
{
		asdfgh=time(NULL);
		srand(asdfgh);
		//declare barber thread;
		pthread_t barber,customerM,timer_thread;
		pthread_attr_t barberAttr, timerAttr;
		pthread_attr_t customerMAttr;

		//define barber, and cutomerMaker default attributes
		pthread_attr_init(&timerAttr);
		pthread_attr_init(&barberAttr);
		pthread_attr_init(&customerMAttr);

		printf("\n");

		//create cutomerMaker
		pthread_create(&customerM,&customerMAttr,customer,NULL);

		//create barber
		pthread_create(&barber,&barberAttr,barberShop,NULL);

		pthread_join(barber,NULL);
		pthread_join(customerM,NULL);

		return 0;
}

void *customer()
{
		int i=0;
		printf("*Customer Maker Created*\n\n");
		fflush(stdout);
		pthread_t customer[seats+1];
		pthread_attr_t customerAttr[seats+1];
		while(i<(seats+1)) /*if there are no free chairs, leave*/
		{
				i++;/*increment count of waiting customer*/
				pthread_attr_init(&customerAttr[i]);
				while(rand()%2!=1)
				{
						sleep(1);/*go to sleep*/
				}
				pthread_create(&customer[i],&customerAttr[i],waiting_Room,NULL);
		}
		pthread_exit(0);/*shop is full,do not wait*/
}

void *waiting_Room()
{
		//take seat
		pthread_mutex_lock(&queue);
		checkQueue();

		sleep(returnTime);
		waiting_Room();
}

void *barberShop()
{
		int loop=0;
		printf("The barber has opened the store.\n");
		fflush(stdout);
		while(loop==0)
		{
				if(current==0)
				{
				printf("\tThe shop is empty, barber is sleeping.\n");
				fflush(stdout);
				pthread_mutex_lock(&sleepa);
				urakam=1;
				pthread_cond_wait(&barberSleep,&sleepa);
				urakam=0;
				pthread_mutex_unlock(&sleepa);
				printf("\t\t\t\tBarber wakes up.\n");
				fflush(stdout);
				}
				else
				{
						printf("\t\t\tBarber begins cutting hair.\n");
						fflush(stdout);
						sleep((rand()%20)/5);
						current--;
						printf("\t\t\t\tHair cut complete, customer leaving store.\n");
						pthread_cond_signal(&barberWorking);
				}
		}
		pthread_exit(0);
}

void checkQueue()
{
		current++;
		printf("\tCustomer has arrived in the waiting room.\t\t\t\t\t\t\t%d Customers in store.\n",current);
		fflush(stdout);
		printf("\t\tCustomer checking chairs.\n");
		fflush(stdout);
		if(current<seats)
		{
				if(urakam==1)
				{
						printf("\t\t\tBarber is sleeping, customer wakes him.\n");
						fflush(stdout);
						pthread_cond_signal(&barberSleep);
				}
				printf("\t\tCustomer takes a seat.\n");
				fflush(stdout);
				pthread_mutex_unlock(&queue);
				pthread_mutex_lock(&wait);
				pthread_cond_wait(&barberWorking,&wait);
				pthread_mutex_unlock(&wait);
				return;
		}
		if(current>=seats)
		{
				printf("\t\tAll chairs full, leaving store.\n");
				fflush(stdout);
				current--;
				pthread_mutex_unlock(&queue);
				return;
		}
}

